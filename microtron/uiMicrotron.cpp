#include "uiMicrotron.h"
#include "ui_uiMicrotron.h"
#include "client.h"

#include <QDebug>
#include <QMessageBox>
#include <qepicspv.h>

uiMicrotron::uiMicrotron(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::uiMicrotron)
{
    ui->setupUi(this);
    QObject::connect(ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));

    pvShutdown = new QEpicsPV("MI-PS-MM:getShutdownCondition.B3");
    // pvRamp     = new QEpicsPV("MI-PS-MM:getRampStatus");
    pvRamp     = new QEpicsPV("MI-PS-MM:getRampState");
    pvSequence = new QEpicsPV("MI-PS-MM:setSequenceState.DISA");
    pvFilament = new QEpicsPV("MI-RF-MAG:getFilamentWorkingHours");
    pvAGPSState = new QEpicsPV("AGPS:getState");
    pvAGPSWarnings = new QEpicsPV("AGPS:getWarningsState");
    pvGunState = new QEpicsPV("MI-PS-MOD-GUN:getState.RVAL");
    pvMagState = new QEpicsPV("MI-PS-MOD-MAG:getState.RVAL");
    pvGunTriggerInterlocks = new QEpicsPV("MI-PS-MOD-GUN:getActiveTrigInterlocks");
    pvMagTriggerInterlocks = new QEpicsPV("MI-PS-MOD-MAG:getActiveTrigInterlocks");
    pvGunStandbyInterlocks = new QEpicsPV("MI-PS-MOD-GUN:getActiveStandbyInterlocks");
    pvMagStandbyInterlocks = new QEpicsPV("MI-PS-MOD-MAG:getActiveStandbyInterlocks");
    pvGunHVInterlocks = new QEpicsPV("MI-PS-MOD-GUN:getActiveHVInterlocks");
    pvMagHVInterlocks = new QEpicsPV("MI-PS-MOD-MAG:getActiveHVInterlocks");
    pvGunTrigger = new QEpicsPV("MI-PS-MOD-GUN:getMessageCodes.B6");
    pvMagTrigger = new QEpicsPV("MI-PS-MOD-MAG:getMessageCodes.B6");

    QObject::connect(pvShutdown, SIGNAL(valueChanged(QVariant)), this, SLOT(rampStatusChanged()));
    QObject::connect(pvSequence, SIGNAL(valueChanged(QVariant)), this, SLOT(rampStatusChanged()));
    QObject::connect(pvRamp,     SIGNAL(valueChanged(QVariant)), this, SLOT(rampStatusChanged()));
//    QObject::connect(pvFilament, SIGNAL(valueChanged(QVariant)), this, SLOT(filamentHoursChanged()));
    QObject::connect(pvAGPSState, SIGNAL(valueChanged(QVariant)), this, SLOT(onAGPSStateChanged()));
    QObject::connect(pvAGPSWarnings, SIGNAL(valueChanged(QVariant)), this, SLOT(onAGPSWarningsChanged()));
    QObject::connect(pvGunState, SIGNAL(valueChanged(QVariant)), this, SLOT(onGunStateChanged()));
    QObject::connect(pvMagState, SIGNAL(valueChanged(QVariant)), this, SLOT(onMagStateChanged()));
    QObject::connect(pvGunTriggerInterlocks, SIGNAL(valueChanged(QVariant)), this, SLOT(onGunInterlocksChanged()));
    QObject::connect(pvMagTriggerInterlocks, SIGNAL(valueChanged(QVariant)), this, SLOT(onMagInterlocksChanged()));
    QObject::connect(pvGunStandbyInterlocks, SIGNAL(valueChanged(QVariant)), this, SLOT(onGunInterlocksChanged()));
    QObject::connect(pvMagStandbyInterlocks, SIGNAL(valueChanged(QVariant)), this, SLOT(onMagInterlocksChanged()));
    QObject::connect(pvGunHVInterlocks, SIGNAL(valueChanged(QVariant)), this, SLOT(onGunInterlocksChanged()));
    QObject::connect(pvMagHVInterlocks, SIGNAL(valueChanged(QVariant)), this, SLOT(onMagInterlocksChanged()));
    QObject::connect(pvGunTrigger, SIGNAL(valueChanged(QVariant)), this, SLOT(onGunTriggerStateChanged()));
    QObject::connect(pvMagTrigger, SIGNAL(valueChanged(QVariant)), this, SLOT(onMagTriggerStateChanged()));
    setFixedSize(width(), height());

    this->trigger = NULL;
    this->set_current_pass = NULL;
    this->scope = NULL;
}

uiMicrotron::~uiMicrotron()
{
    delete ui;
}

void uiMicrotron::on_btnRampUp_clicked()
{
//    Client::writePV("MI-PS-MM:setSequence", "TEST6");
//    Client::writePV("MI-PS-MM:setSequenceState", "RUN");
//    Client::writePV("MI-PS-MM:setSequenceState", "");
}

void uiMicrotron::on_btnReset_clicked()
{
    Client::writePV("MI-GE:reset", 1);
    Client::writePV("MI-GE:resetInterlocks", 1);
}

void uiMicrotron::on_btnPowerOff_clicked()
{
    Client::writePV("MI-PS:disableRackPower", 1);
}

void uiMicrotron::on_btnClose_clicked()
{
   this->close();
}

void uiMicrotron::on_btnPowerOn_clicked()
{
    Client::writePV("MI-PS:enableRackPower", 1);
}

void uiMicrotron::on_btnMagnetOff_clicked()
{
    Client::writePV("MI-PS-MM:enable", 0);
}
/**/
void uiMicrotron::on_btnMagnetOn_clicked()
{
    Client::writePV("MI-PS-MM:enable", 1);
}

void uiMicrotron::on_btnFilamentOff_clicked()
{
    Client::writePV("MI-RF-MAG:disableFilament", 1);
}
/**/
void uiMicrotron::on_btnFilamentOn_clicked()
{
    Client::writePV("MI-RF-MAG:enableFilament", 1);
}
/**/
void uiMicrotron::on_btnHighVoltageOff_clicked()
{
    Client::writePV("MI-PS-MOD:disableHighVoltage", 1);
}

void uiMicrotron::on_btnHighVoltageOn_clicked()
{
    Client::writePV("MI-PS-MOD:enableHighVoltage", 1);
}
/**/
void uiMicrotron::rampStatusChanged()
{
//    ui->btnRampUp->setEnabled(this->pvShutdown->get().toInt() > 0 && this->pvRamp->get().toInt() == 0 && this->pvSequence->get().toInt() == 0);
//    ui->btnRampDown->setEnabled(this->pvShutdown->get().toInt() > 0 && this->pvRamp->get().toInt() == 2 && this->pvSequence->get().toInt() == 0);

    ui->ledRampUp->setValue(pvRamp->get().toInt() == 1);
    ui->ledRampDown->setValue(pvRamp->get().toInt() == 2);
    ui->ledRampReady->setValue(pvRamp->get().toInt() == 0);
    ui->ledRampError->setValue(pvRamp->get().toInt() == 4);
}
/**/
//void uiMicrotron::filamentHoursChanged()
//{
//    ui->lblHours->setText(QString::number(this->pvFilament->get().toInt() / 3600));
//}
/**/
void uiMicrotron::onAGPSStateChanged()
{
    int value = this->pvAGPSState->get().toInt();
    if(value == 0)
    {
        ui->ledGunState->setValue(0);
    }
    else if(value == 1 || value == 2)
    {
        ui->ledGunState->setValue(2);
    }
    else if(value == 3)
    {
        ui->ledGunState->setValue(1);
    }
    else if(value == 4)
    {
        ui->ledGunState->setValue(1);
    }
    else if(value == 20)
    {
        ui->ledGunState->setValue(3);
    }
    else
    {
        ui->ledGunState->setValue(0);
    }
}

void uiMicrotron::onAGPSWarningsChanged()
{
    ui->ledGunWarnings->setValue(this->pvAGPSWarnings->get().toInt() > 0);
}

void uiMicrotron::on_btnSequencer_clicked()
{
    OPEN_UI(this->trigger, MicrotronTriggerWindow, this);
}


void uiMicrotron::on_btnSetCurrent_clicked()
{
    QString goldenHash = "675eba8ed190a54e63361c44dac965fa2d70ddd45c6d3bfdc64c71f7c360df41";
    FormPassword *passwordWindow = new FormPassword(goldenHash, this);
//    passwordWindow->show();
    QObject::connect(passwordWindow, SIGNAL(authenticated()), this, SLOT(open_set_current()));

    if (!FormPassword::dialogOpen) {
        passwordWindow->show();
        FormPassword::dialogOpen = true;
    }
}

void uiMicrotron::open_set_current()
{
    FormSetCurrent *set_current = new FormSetCurrent();
    set_current->show();
}

void uiMicrotron::on_btnCycle_clicked()
{
    bool ok;
    unsigned int cycles = ui->txtCycles->text().toUInt(&ok);
    if(!ok || cycles == 0) {
        QMessageBox::warning(this, "Warning.", "Enter a valid integer.", QMessageBox::Ok);
        return;
    }

    QProcess* p = new QProcess;
    p->setWorkingDirectory(getenv("HOME"));
    p->start("gnome-terminal --geometry 100x30 -x Main_Magnet_Ramp.py --cycle " + QString::number(cycles));
}

void::uiMicrotron::onGunStateChanged()
{
    int value = this->pvGunState->get().toInt();
    if(value == 0)
    {
        ui->ledGunModState->setValue(0);
    }
    else if(value == 3 || value == 6)
    {
        ui->ledGunModState->setValue(1);
    }
    else
    {
        ui->ledGunModState->setValue(2);
    }

}


void::uiMicrotron::onMagStateChanged()
{
    int value = this->pvMagState->get().toInt();
    if(value == 0)
    {
        ui->ledGunModState_2->setValue(0);
    }
    else if(value == 3 || value == 6)
    {
        ui->ledGunModState_2->setValue(1);
    }
    else
    {
        ui->ledGunModState_2->setValue(2);
    }
}

void::uiMicrotron::onGunInterlocksChanged()
{
    int value_trig_interlocks = this->pvGunTriggerInterlocks->get().toInt();
    int value_standby_interlocks = this->pvGunStandbyInterlocks->get().toInt();
    int value_hv_interlocks = this->pvGunHVInterlocks->get().toInt();
    if((value_trig_interlocks == 0 || value_trig_interlocks == 2) && value_standby_interlocks == 0 && value_hv_interlocks == 0)
    {

        ui->ledGunInterlocks->setValue(0);

    }
    else
    {
        ui->ledGunInterlocks->setValue(3);
    }
}

void::uiMicrotron::onMagInterlocksChanged()
{
    int value_trig_interlocks = this->pvMagTriggerInterlocks->get().toInt();
    int value_standby_interlocks = this->pvMagStandbyInterlocks->get().toInt();
    int value_hv_interlocks = this->pvMagHVInterlocks->get().toInt();
    if((value_trig_interlocks == 0 || value_trig_interlocks == 2) && value_standby_interlocks == 0 && value_hv_interlocks == 0)
    {

        ui->ledMagInterlocks->setValue(0);

    }
    else
    {
        ui->ledMagInterlocks->setValue(3);
    }
}

void::uiMicrotron::onGunTriggerStateChanged()
{
    int value = this->pvGunTrigger->get().toInt();
    if(value == 0)
    {
        ui->ledGunTrigger->setValue(1);
    }
    else
    {
        ui->ledGunTrigger->setValue(0);
    }
}

void::uiMicrotron::onMagTriggerStateChanged()
{
    int value = this->pvMagTrigger->get().toInt();
    if(value == 0)
    {
        ui->ledMagTrigger->setValue(1);
    }
    else
    {
        ui->ledMagTrigger->setValue(0);
    }
}


void uiMicrotron::on_btnTimers_clicked()
{
    FormTimer* timers = new FormTimer(this);
    timers->show();
}

void uiMicrotron::on_btnScope_clicked()
{
    OPEN_UI(this->scope,
            ScopesWindow,
            "Microtron Signals",
            {"MI-DI-OSC:wave:CH1", "MI-DI-OSC:wave:CH2", "MI-DI-OSC:wave:CH3", "MI-DI-OSC:wave:CH4"},
            {"Reflected Power", "Magnetron", "Gun Current", "Deflection Tube"},
            this);
}
