#include "uiSRPowerSupplyDetails.h"
#include "ui_uiSRPowerSupplyDetails.h"

uiSRPowerSupplyDetails::uiSRPowerSupplyDetails(QString magnet, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::uiSRPowerSupplyDetails)
{
    ui->setupUi(this);
    CONNECT_CLOSE_BUTTON;

    group = magnet;
    this->setWindowTitle(group + " Details");
    SET_GROUP(QELabel);
    SET_GROUP(QENumericEdit);
    SET_GROUP(QEPushButton);
    SET_GROUP(QELineEdit);
    ui->cbMode->setVariableNameProperty(group + ":setMode");

    pvState    = new QEpicsPV(group + ":getStateHandler");
    pvSequence = new QEpicsPV(group + ":getStateSequencer");
    pvIload    = new QEpicsPV(group + ":getIload");
    pvStatus   = new QEpicsPV("Machine:Status");
    QObject::connect(pvState,    SIGNAL(valueChanged(QVariant)), this, SLOT(stateHandler_changed(QVariant)));
    QObject::connect(pvSequence, SIGNAL(valueChanged(QVariant)), this, SLOT(stateSequencer_changed(QVariant)));
    QObject::connect(pvIload,    SIGNAL(valueChanged(QVariant)), this, SLOT(onDipoleCurrentChanged(QVariant)));
    QObject::connect(pvStatus,   SIGNAL(valueChanged(QVariant)), this, SLOT(onMachineStatusChanged(QVariant)));

}

uiSRPowerSupplyDetails::~uiSRPowerSupplyDetails()
{
    delete ui;
}

void uiSRPowerSupplyDetails::stateHandler_changed(QVariant value)
{
    int state = value.toInt();
    if(state == STATE_FAULT) {
        ui->ledOpen->setValue(0);
        ui->ledOFF->setValue(0);
        ui->ledStandby->setValue(0);
        ui->ledON->setValue(0);
        ui->ledFault->setValue(1);
    }
    else if(state == STATE_ON) {
        ui->ledOpen->setValue(0);
        ui->ledOFF->setValue(0);
        ui->ledStandby->setValue(0);
        ui->ledON->setValue(1);
        ui->ledFault->setValue(0);
    }
    else if(state == STATE_STANDBY) {
        ui->ledOpen->setValue(0);
        ui->ledOFF->setValue(0);
        ui->ledStandby->setValue(1);
        ui->ledON->setValue(0);
        ui->ledFault->setValue(0);
    }
    else if(state == STATE_OFF) {
        ui->ledOpen->setValue(0);
        ui->ledOFF->setValue(1);
        ui->ledStandby->setValue(0);
        ui->ledON->setValue(0);
        ui->ledFault->setValue(0);
    }
    else if(state == STATE_OPENLOOP) {
        ui->ledOpen->setValue(1);
        ui->ledOFF->setValue(0);
        ui->ledStandby->setValue(0);
        ui->ledON->setValue(0);
        ui->ledFault->setValue(0);
    }
    else {
        ui->ledOpen->setValue(0);
        ui->ledOFF->setValue(0);
        ui->ledStandby->setValue(0);
        ui->ledON->setValue(0);
        ui->ledFault->setValue(0);
    }

    if(state == STATE_OPENLOOP) {
        ui->btnOpenloop->setEnabled(false);
        ui->btnOFF->setEnabled(true);
        ui->btnStandby->setEnabled(false);
        ui->btnON->setEnabled(false);
    }
    else if(state == STATE_OFF) {
        ui->btnOpenloop->setEnabled(true);
        ui->btnOFF->setEnabled(false);
        ui->btnStandby->setEnabled(true);
        ui->btnON->setEnabled(false);
    }
    else if(state == STATE_STANDBY) {
        ui->btnOpenloop->setEnabled(false);
        ui->btnOFF->setEnabled(true);
        ui->btnStandby->setEnabled(false);
        ui->btnON->setEnabled(true);
    }
    else if(state == STATE_ON) {
        ui->btnOpenloop->setEnabled(false);
        ui->btnOFF->setEnabled(false);
        ui->btnStandby->setEnabled(true);
        ui->btnON->setEnabled(false);
    }
}

void uiSRPowerSupplyDetails::stateSequencer_changed(QVariant value)
{
    int state = value.toInt();
    if(state == SEQUENCE_SEMIAUTO || state == SEQUENCE_SEMIAUTO_ACTIVE) {
        ui->ledSemiAuto->setValue(1);
        ui->ledAuto->setValue(0);
        ui->ledManual->setValue(0);
    }
    else if(state == SEQUENCE_AUTO || state == SEQUENCE_AUTO_ACTIVE) {
        ui->ledSemiAuto->setValue(0);
        ui->ledAuto->setValue(1);
        ui->ledManual->setValue(0);
    }
    else if(state == SEQUENCE_MANUAL || state == SEQUENCE_MANUAL_ACTIVE) {
        ui->ledSemiAuto->setValue(0);
        ui->ledAuto->setValue(0);
        ui->ledManual->setValue(1);
    }
    else {
        ui->ledSemiAuto->setValue(0);
        ui->ledAuto->setValue(0);
        ui->ledManual->setValue(0);
    }

    ui->ledRamping->setValue(state == SEQUENCE_AUTO_ACTIVE || state == SEQUENCE_SEMIAUTO_ACTIVE || state == SEQUENCE_MANUAL_ACTIVE);
}

void uiSRPowerSupplyDetails::on_pushButton_4_clicked() { tuning = new uiSRPowerSupplyTuning(group); tuning->show(); }

void uiSRPowerSupplyDetails::on_pushButton_8_clicked() { plotter = new uiSRPowerSupplyPlotter(group); plotter->show(); }

void uiSRPowerSupplyDetails::on_pushButton_6_clicked() { uiReadings = new uiSRPowerSupplyReadings(group); uiReadings->show(); }

void uiSRPowerSupplyDetails::on_pushButton_5_clicked()
{
    if(this->group == "SR-PS-BM")
    {
        dipoleFaults = new FormDipoleFaults;
        showUI(dipoleFaults);
    }
    else
    {
        uiFaults = new uiSRPowerSupplyFaults(group);
        showUI(uiFaults);
    }
}

void uiSRPowerSupplyDetails::on_btnWaveforms_clicked()
{
    this->waveforms = new FormWaveformSettings(group);
    this->waveforms->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, this->waveforms->size(), qApp->desktop()->availableGeometry()));
    this->waveforms->show();
}

void uiSRPowerSupplyDetails::on_btnFirmwareSettings_clicked()
{
    QString goldenHash = "675eba8ed190a54e63361c44dac965fa2d70ddd45c6d3bfdc64c71f7c360df41";
    FormPassword * authObj = new FormPassword(goldenHash, this);
    QObject::connect(authObj, SIGNAL(authenticated()), this, SLOT(showFirmwareSettingsParameters()));

    if (!FormPassword::dialogOpen) {
        authObj->show();
        FormPassword::dialogOpen = true;
    }
 }

void uiSRPowerSupplyDetails::showFirmwareSettingsParameters()
{
    this->parameters = new FormParameters(this->group);
    this->parameters->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, this->parameters->size(), qApp->desktop()->availableGeometry()));
    this->parameters->show();
}

void uiSRPowerSupplyDetails::onDipoleCurrentChanged(QVariant value)
{
    Q_UNUSED(value);
//    int state = this->pvState->get().toInt();
//    double load = value.toDouble();
//    if(state == STATE_OFF || state == STATE_ON) {
//        ui->btnOpenloop->setEnabled(false);
//        ui->btnOFF->setEnabled(false);
//        if( (this->group == "SR-PS-BM" && load < 5.0) || this->group != "SR-PS-BM" )
//        ui->btnStandby->setEnabled(true);
//        ui->btnON->setEnabled(false);
//    }
}

void uiSRPowerSupplyDetails::onMachineStatusChanged(QVariant value)
{
    bool condition = value.toInt() != 3 && value.toInt() != 6 && value.toInt() != 7;
    ui->txtReference->setEnabled(condition);
    ui->btnOpenloop->setEnabled(condition);
    ui->btnOFF->setEnabled(condition);
    ui->btnStandby->setEnabled(condition);
}
