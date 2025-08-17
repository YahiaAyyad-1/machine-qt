#include "FormBoosterDCPower.h"
#include "ui_FormBoosterDCPower.h"

FormBoosterDCPower::FormBoosterDCPower(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormBoosterDCPower)
{
    ui->setupUi(this);

    this->pvBMState = new QEpicsPV("BO-PS-BM:getState");
    this->pvQFState = new QEpicsPV("BO-PS-QF:getState");
    this->pvQDState = new QEpicsPV("BO-PS-QD:getState");

    this->pvBMInterlocks1 = new QEpicsPV("BO-PS-BM:getRegulationInterlocks");
    this->pvBMInterlocks2 = new QEpicsPV("BO-PS-BM:getMasterHardwareInterlocks");
    this->pvBMInterlocks3 = new QEpicsPV("BO-PS-BM:getMasterSoftwareInterlocks");
    this->pvBMInterlocks4 = new QEpicsPV("BO-PS-BM:getSlave1HardwareInterlocks");
    this->pvBMInterlocks5 = new QEpicsPV("BO-PS-BM:getSlave1SoftwareInterlocks");
    this->pvBMInterlocks6 = new QEpicsPV("BO-PS-BM:getSlave2HardwareInterlocks");
    this->pvBMInterlocks7 = new QEpicsPV("BO-PS-BM:getSlave2SoftwareInterlocks");

    this->pvQFInterlocks1 = new QEpicsPV("BO-PS-QF:getRegulationInterlocks");
    this->pvQFInterlocks2 = new QEpicsPV("BO-PS-QF:getHardwareInterlocks");
    this->pvQFInterlocks3 = new QEpicsPV("BO-PS-QF:getSoftwareInterlocks");

    this->pvQDInterlocks1 = new QEpicsPV("BO-PS-QD:getRegulationInterlocks");
    this->pvQDInterlocks2 = new QEpicsPV("BO-PS-QD:getHardwareInterlocks");
    this->pvQDInterlocks3 = new QEpicsPV("BO-PS-QD:getSoftwareInterlocks");

    QObject::connect(this->pvBMState, SIGNAL(valueChanged(QVariant)), this, SLOT(powerState_Changed()));
    QObject::connect(this->pvQFState, SIGNAL(valueChanged(QVariant)), this, SLOT(powerState_Changed()));
    QObject::connect(this->pvQDState, SIGNAL(valueChanged(QVariant)), this, SLOT(powerState_Changed()));

    QObject::connect(this->pvBMInterlocks1, SIGNAL(valueChanged(QVariant)), this, SLOT(powerInterlocks_Changed()));
    QObject::connect(this->pvBMInterlocks2, SIGNAL(valueChanged(QVariant)), this, SLOT(powerInterlocks_Changed()));
    QObject::connect(this->pvBMInterlocks3, SIGNAL(valueChanged(QVariant)), this, SLOT(powerInterlocks_Changed()));

    QObject::connect(this->pvQFInterlocks1, SIGNAL(valueChanged(QVariant)), this, SLOT(powerInterlocks_Changed()));
    QObject::connect(this->pvQFInterlocks2, SIGNAL(valueChanged(QVariant)), this, SLOT(powerInterlocks_Changed()));
    QObject::connect(this->pvQFInterlocks3, SIGNAL(valueChanged(QVariant)), this, SLOT(powerInterlocks_Changed()));

    QObject::connect(this->pvQDInterlocks1, SIGNAL(valueChanged(QVariant)), this, SLOT(powerInterlocks_Changed()));
    QObject::connect(this->pvQDInterlocks2, SIGNAL(valueChanged(QVariant)), this, SLOT(powerInterlocks_Changed()));
    QObject::connect(this->pvQDInterlocks3, SIGNAL(valueChanged(QVariant)), this, SLOT(powerInterlocks_Changed()));

    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
}

FormBoosterDCPower::~FormBoosterDCPower()
{
    delete ui;
}

void FormBoosterDCPower::powerState_Changed()
{
    QStringList states = this->pvBMState->getEnum();
    QString bmState = states[this->pvBMState->get().toInt()];
    QString qfState = states[this->pvQFState->get().toInt() >= states.length() ? 11 : this->pvQFState->get().toInt()];
    QString qdState = states[this->pvQDState->get().toInt() >= states.length() ? 11 : this->pvQDState->get().toInt()];

    this->ui->ledBMStandby->setValue( bmState == "Standby" ? 1 : 0 );
    this->ui->ledBMRush->setValue( bmState == "Inrush sequence" ? 1 : 0 );
    this->ui->ledBMPower->setValue( bmState == "Power on" ? 1 : 0 );
    this->ui->ledBMPulse->setValue( bmState == "Pulse on" ? 1 : 0 );
    this->ui->ledBMStop->setValue( bmState == "Stopping sequence" ? 1 : 0 );

    this->ui->ledQFStandby->setValue( qfState == "Standby" ? 1 : 0 );
    this->ui->ledQFRush->setValue( qfState == "Inrush sequence" ? 1 : 0 );
    this->ui->ledQFPower->setValue( qfState == "Power on" ? 1 : 0 );
    this->ui->ledQFPulse->setValue( qfState == "Pulse on" ? 1 : 0 );
    this->ui->ledQFStop->setValue( qfState == "Stopping sequence" ? 1 : 0 );

    this->ui->ledQDStandby->setValue( qdState == "Standby" ? 1 : 0 );
    this->ui->ledQDRush->setValue( qdState == "Inrush sequence" ? 1 : 0 );
    this->ui->ledQDPower->setValue( qdState == "Power on" ? 1 : 0 );
    this->ui->ledQDPulse->setValue( qdState == "Pulse on" ? 1 : 0 );
    this->ui->ledQDStop->setValue( qdState == "Stopping sequence" ? 1 : 0 );
}

void FormBoosterDCPower::powerInterlocks_Changed()
{
    int bmLock1 = this->pvBMInterlocks1->get().toInt();
    int bmLock2 = this->pvBMInterlocks2->get().toInt();
    int bmLock3 = this->pvBMInterlocks3->get().toInt();
    int bmLock4 = this->pvBMInterlocks4->get().toInt();
    int bmLock5 = this->pvBMInterlocks5->get().toInt();
    int bmLock6 = this->pvBMInterlocks6->get().toInt();
    int bmLock7 = this->pvBMInterlocks7->get().toInt();

    int qfLock1 = this->pvQFInterlocks1->get().toInt();
    int qfLock2 = this->pvQFInterlocks2->get().toInt();
    int qfLock3 = this->pvQFInterlocks3->get().toInt();

    int qdLock1 = this->pvQDInterlocks1->get().toInt();
    int qdLock2 = this->pvQDInterlocks2->get().toInt();
    int qdLock3 = this->pvQDInterlocks3->get().toInt();

    this->ui->ledBMInterlocks->setValue(bmLock1 || bmLock2 || bmLock3 || bmLock4 || bmLock5 || bmLock6 || bmLock7);
    this->ui->ledQFInterlocks->setValue(qfLock1 || qfLock2 || qfLock3);
    this->ui->ledQDInterlocks->setValue(qdLock1 || qdLock2 || qdLock3);
}

void FormBoosterDCPower::on_btnConfig_clicked()
{
    this->config = new FormDCConfig;
    this->config->show();
}

void FormBoosterDCPower::on_btnBMPower_clicked()
{
    Client::writePV("BO-PS-BM:enablePower", 1);
    Client::writePV("BO-PS-BM:enablePulse", 0);
}

void FormBoosterDCPower::on_btnQFPower_clicked()
{
    Client::writePV("BO-PS-QF:enablePower", 1);
    Client::writePV("BO-PS-QF:enablePulse", 0);
}

void FormBoosterDCPower::on_btnQDPower_clicked()
{
    Client::writePV("BO-PS-QD:enablePower", 1);
    Client::writePV("BO-PS-QD:enablePulse", 0);
}

void FormBoosterDCPower::on_btnQFInterlocks_clicked()
{
    this->dcInterlocks = new FormDCInterlocks("QF");
    this->dcInterlocks->show();
}

void FormBoosterDCPower::on_btnQDInterlocks_clicked()
{
    this->dcInterlocks = new FormDCInterlocks("QD");
    this->dcInterlocks->show();
}

void FormBoosterDCPower::on_btnBMInterlocks_clicked()
{
    this->bmInterlocks = new FormBMInterlocks;
    this->bmInterlocks->show();
}
