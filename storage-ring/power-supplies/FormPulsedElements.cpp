#include "FormPulsedElements.h"
#include "ui_FormPulsedElements.h"

FormPulsedElements::FormPulsedElements(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormPulsedElements)
{
    ui->setupUi(this);
    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
    CONNECT_CLOSE_BUTTON;

    this->pid = NULL;
    this->mode = new QEpicsPV("SR-PS-INS:setOperationMode");
    this->voltage = new QEpicsPV("SR-PS-INK:getVoltage");
    this->machineStatus = new QEpicsPV("Machine:Status");
    QObject::connect(this->mode, SIGNAL(valueChanged(QVariant)), this, SLOT(onModeChanged(QVariant)));
    QObject::connect(this->voltage, SIGNAL(valueChanged(QVariant)), this, SLOT(onKickerVoltageChanged(QVariant)));

    this->pvSeptumCurrentLimit = new QEpicsPV("INJ-SEP-DCCT-LIM:isInterlock");
    this->pvSeptumMs = new QEpicsPV("INJ-SEP-ID09-GAP:isInterlock");
    this->pvSeptumHeseb = new QEpicsPV("INJ-SEP-UND-GAP:isInterlock");
    this->pvSeptumBeats = new QEpicsPV("INJ-SEP-ID10-GAP:isInterlock");
    QObject::connect(this->pvSeptumCurrentLimit, SIGNAL(valueChanged(QVariant)), this, SLOT(onSeptumInterlock()));
    QObject::connect(this->pvSeptumMs, SIGNAL(valueChanged(QVariant)), this, SLOT(onSeptumInterlock()));
    QObject::connect(this->pvSeptumHeseb, SIGNAL(valueChanged(QVariant)), this, SLOT(onSeptumInterlock()));
    QObject::connect(this->pvSeptumBeats, SIGNAL(valueChanged(QVariant)), this, SLOT(onSeptumInterlock()));
    QObject::connect(this->machineStatus, SIGNAL(valueChanged(QVariant)), this, SLOT(onMachineStatusChanged(QVariant)));
}

FormPulsedElements::~FormPulsedElements()
{
    delete ui;
}

void FormPulsedElements::onMachineStatusChanged(QVariant value)
{
    bool enabled;

    enabled = value.toInt() != 3 && value.toInt() != 6 && value.toInt() != 7;
    ui->btnInjKickerTrigOn->setEnabled(enabled);
}

void FormPulsedElements::on_btnPID_clicked()
{
    if(!this->pid)
        this->pid = new FormPID;
    showUI(this->pid);
    this->pid = NULL;
}

void FormPulsedElements::onModeChanged(QVariant value)
{
    ui->txtPeakCurrent->setEnabled(value.toInt());
    ui->txtVoltage->setEnabled(!value.toInt());
}

void FormPulsedElements::on_btnON_clicked()
{
    Client::writePV("SR-PS-INS:enableTrigger", 1);
    Client::writePV("SR-PS-INS:sequenceFeedback.PROC", 1);
    Client::writePV("SR-PS-INS:sequenceSetpoint.PROC", 1);
}

void FormPulsedElements::on_btnOFF_clicked()
{
    Client::writePV("SR-PS-INS:disableTrigger", 1);
    Client::writePV("SR-PS-INS:getPID.FBON", 0);
    Client::writePV("SR-PS-INS:setVoltage", 0);
}

void FormPulsedElements::onKickerVoltageChanged(QVariant value) {
    ui->lblKick->setText(QString::number(value.toDouble() * 0.2578 / 1000.0) + " mrad");
}

void FormPulsedElements::on_btnSeptumInterlocks_clicked()
{
    FormSeptumInterlocks* septum_interlocks = new FormSeptumInterlocks(this);
    septum_interlocks->show();
}

void FormPulsedElements::onSeptumInterlock(){
    int ms_interlock = this->pvSeptumMs->get().toInt();
    int beats_interlock = this->pvSeptumBeats->get().toInt();
    int heseb_interlock = this->pvSeptumHeseb->get().toInt();
    int current_limit_interlock = this->pvSeptumCurrentLimit->get().toInt();

    if (ms_interlock == 0 || beats_interlock == 0 || heseb_interlock == 0 || current_limit_interlock == 0)
    {
        ui->ledSeptumInterlocks->setValue(0);
    }
    else
    {
        ui->ledSeptumInterlocks->setValue(1);

    }
}
