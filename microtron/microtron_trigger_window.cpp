#include "microtron_trigger_window.h"
#include "ui_microtron_trigger_window.h"
#include "client.h"
#include "qdebug.h"

MicrotronTriggerWindow::MicrotronTriggerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MicrotronTriggerWindow)
{
    ui->setupUi(this);

    triggerMode = new QEpicsPV("TRIGGER:MODE");
    agpsChecked = new QEpicsPV("TRIGGER:MAINTENANCE:AGPS");
    magModChecked = new QEpicsPV("TRIGGER:MAINTENANCE:MAGMOD");
    gunModChecked = new QEpicsPV("TRIGGER:MAINTENANCE:GUNMOD");
    machineState = new QEpicsPV("MI:trigger");
    agpsAckOn = new QEpicsPV("AGPS:ACK:ON");

    pvAGPSState = new QEpicsPV("AGPS:getState");
    pvGunModState = new QEpicsPV("MI-PS-MOD-GUN:getState.RVAL");
    pvMagModState = new QEpicsPV("MI-PS-MOD-MAG:getState.RVAL");

    QObject::connect(this->triggerMode, SIGNAL(valueChanged(QVariant)), this, SLOT(triggerModeChanged(QVariant)));
    QObject::connect(this->machineState, SIGNAL(valueChanged(QVariant)), this, SLOT(machineStateChanged(QVariant)));

    QObject::connect(this->agpsChecked, SIGNAL(valueChanged(QVariant)), this, SLOT(checkDevicesToTrigger(QVariant)));
    QObject::connect(this->magModChecked, SIGNAL(valueChanged(QVariant)), this, SLOT(checkDevicesToTrigger(QVariant)));
    QObject::connect(this->gunModChecked, SIGNAL(valueChanged(QVariant)), this, SLOT(checkDevicesToTrigger(QVariant)));

    QObject::connect(pvAGPSState, SIGNAL(valueChanged(QVariant)), this, SLOT(onAGPSStateChanged()));
    QObject::connect(pvGunModState, SIGNAL(valueChanged(QVariant)), this, SLOT(onGunModStateChanged()));
    QObject::connect(pvMagModState, SIGNAL(valueChanged(QVariant)), this, SLOT(onMagModStateChanged()));

    this->triggerOnTimer = new QTimer(this);
    QObject::connect(this->triggerOnTimer, SIGNAL(timeout()), this, SLOT(onTriggerOnTimeout()));

    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    while (!this->agpsChecked->isConnected() || !this->gunModChecked->isConnected() || !this->magModChecked->isConnected()) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    this->ui->AGPSCheckBox->setChecked(agpsChecked->get().toBool());
    this->ui->MagModCheckBox->setChecked(magModChecked->get().toBool());
    this->ui->eGunModCheckBox->setChecked(gunModChecked->get().toBool());
}

MicrotronTriggerWindow::~MicrotronTriggerWindow()
{
    delete ui;
}

void MicrotronTriggerWindow::on_btnEmergency_clicked()
{
    Client::writePV("MI-SEQ:disableTrigger.PROC", 1);
}

void MicrotronTriggerWindow::on_trigger_state_label_dbValueChanged(QString state)
{
    if(state == "Microtron Trigger is ON")
    {
        ui->microtron_trigger_is_on_label->setStyleSheet("background-color: rgb(138, 226, 52)");
        ui->microtron_trigger_is_off_label->setStyleSheet("");
    } else if (state == "Microtron Trigger is OFF")
    {
        ui->microtron_trigger_is_on_label->setStyleSheet("");
        ui->microtron_trigger_is_off_label->setStyleSheet("background-color: rgb(252, 233, 79)");
    } else
    {
        ui->microtron_trigger_is_on_label->setStyleSheet("");
        ui->microtron_trigger_is_off_label->setStyleSheet("");
    }
}

void MicrotronTriggerWindow::machineStateChanged(QVariant state)
{
    const int standby = 0;
    const int triggerOff = 1;
    const int triggerOn = 2;
    if (state == standby)
    {
        ui->btnOperationMode->setEnabled(true);
        ui->btnMaintenanceMode->setEnabled(true);
        ui->btnTriggerOff->setStyleSheet("");
        ui->btnTriggerOn->setStyleSheet("");
    } else
    {
        ui->btnOperationMode->setEnabled(false);
        ui->btnMaintenanceMode->setEnabled(false);
        if (state == triggerOff)
        {
            ui->btnTriggerOff->setStyleSheet("background-color: rgb(138, 226, 52)");
        } else if (state == triggerOn)
        {
            ui->btnTriggerOn->setStyleSheet("background-color: rgb(138, 226, 52)");
        }
    }

    this->triggerModeChanged(triggerMode->get());
}

void MicrotronTriggerWindow::triggerModeChanged(QVariant val)
{
    /*
      val = 0: Operation
      val = 1; Maintenance
    */
    if (val == 0) {
        this->ui->btnOperationMode->setStyleSheet("background-color: rgb(138, 226, 52)");
        this->ui->btnMaintenanceMode->setStyleSheet("");
        this->ui->devicesToTriggerGroupBox->hide();
    } else {
        this->ui->btnOperationMode->setStyleSheet("");
        this->ui->btnMaintenanceMode->setStyleSheet("background-color: rgb(255, 0, 0)");
        this->ui->devicesToTriggerGroupBox->show();
    }
}

void MicrotronTriggerWindow::on_btnClose_clicked()
{
   this->close();
}

void MicrotronTriggerWindow::on_btnMaintenanceMode_clicked()
{
    QString goldenHash = "a665a45920422f9d417e4867efdc4fb8a04a1f3fff1fa07e998e86f7f7a27ae3";
    FormPassword* authObj = new FormPassword(goldenHash, this);
    QObject::connect(authObj, SIGNAL(authenticated()), this, SLOT(enableMaintenanceMode()));

    if (!FormPassword::dialogOpen) {
        authObj->show();
        FormPassword::dialogOpen = true;
    }
}

void MicrotronTriggerWindow::enableMaintenanceMode() {
    Client::writePV("TRIGGER:MODE", 1);
}

void MicrotronTriggerWindow::checkDevicesToTrigger(QVariant val)
{
    Q_UNUSED(val)
    if (!this->agpsChecked->get().toBool() && !this->gunModChecked->get().toBool() && !this->magModChecked->get().toBool())
        this->ui->btnTriggerOn->setEnabled(0);
    else
        this->ui->btnTriggerOn->setEnabled(1);
}

void MicrotronTriggerWindow::onAGPSStateChanged()
{
    int value = this->pvAGPSState->get().toInt();
    if(value == 0)
    {
        this->ui->ledAGPSState->setValue(0);
    }
    else if(value == 1 || value == 2)
    {
        this->ui->ledAGPSState->setValue(2);
    }
    else if(value == 3)
    {
        this->ui->ledAGPSState->setValue(1);
    }
    else if(value == 4)
    {
        this->ui->ledAGPSState->setValue(1);
    }
    else if(value == 20)
    {
        this->ui->ledAGPSState->setValue(3);
    }
    else
    {
        this->ui->ledAGPSState->setValue(0);
    }
}

void::MicrotronTriggerWindow::onGunModStateChanged()
{
    int value = this->pvGunModState->get().toInt();
    if(value == 0)
    {
        this->ui->ledGunModState->setValue(0);
    }
    else if(value == 3 || value == 6)
    {
        this->ui->ledGunModState->setValue(1);
    }
    else
    {
        this->ui->ledGunModState->setValue(2);
    }
}

void::MicrotronTriggerWindow::onMagModStateChanged()
{
    int value = this->pvMagModState->get().toInt();
    if(value == 0)
    {
        this->ui->ledMagModState->setValue(0);
    }
    else if(value == 3 || value == 6)
    {
        this->ui->ledMagModState->setValue(1);
    }
    else
    {
        this->ui->ledMagModState->setValue(2);
    }
}

void MicrotronTriggerWindow::on_btnTriggerOn_clicked()
{
    const int triggerOn = 2;
    Client::writePV("MI:trigger", triggerOn);
    this->triggerOnTimer->start(2000);
}

void MicrotronTriggerWindow::onTriggerOnTimeout()
{
    const int standby = 0;
    const int acknowledged = 1;
    const int processing = 2;
    if(agpsAckOn->get() != acknowledged && agpsAckOn->get() != processing)
        Client::writePV("MI:trigger", standby);
    this->triggerOnTimer->stop();
}
