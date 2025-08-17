#include "FormBoosterPS.h"
#include "ui_FormBoosterPS.h"

#include "client.h"

FormBoosterPS::FormBoosterPS(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormBoosterPS)
{
    ui->setupUi(this);

    this->pvTiming1 = new QEpicsPV("GBL-TI-EVR0-P1:isEnabled");
    this->pvTiming2 = new QEpicsPV("GBL-TI-EVR0-P2:isEnabled");
    this->pvTiming3 = new QEpicsPV("GBL-TI-EVR0-P3:isEnabled");

    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
    QObject::connect(this->pvTiming1, SIGNAL(valueChanged(QVariant)), this, SLOT(timingEnabled_Changed()));
    QObject::connect(this->pvTiming2, SIGNAL(valueChanged(QVariant)), this, SLOT(timingEnabled_Changed()));
    QObject::connect(this->pvTiming3, SIGNAL(valueChanged(QVariant)), this, SLOT(timingEnabled_Changed()));

    // this->timingEnabled_Changed();
    this->pvBMInterlocks[0] = new QEpicsPV("BO-PS-BM:getRegulationInterlocks");
    this->pvBMInterlocks[1] = new QEpicsPV("BO-PS-BM:getMasterHardwareInterlocks");
    this->pvBMInterlocks[2] = new QEpicsPV("BO-PS-BM:getMasterSoftwareInterlocks");
    this->pvBMInterlocks[3] = new QEpicsPV("BO-PS-BM:getSlave1HardwareInterlocks");
    this->pvBMInterlocks[4] = new QEpicsPV("BO-PS-BM:getSlave2HardwareInterlocks");
    this->pvBMInterlocks[5] = new QEpicsPV("BO-PS-BM:getSlave1SoftwareInterlocks");
    this->pvBMInterlocks[6] = new QEpicsPV("BO-PS-BM:getSlave2SoftwareInterlocks");

    this->pvQFInterlocks[0] = new QEpicsPV("BO-PS-QF:getRegulationInterlocks");
    this->pvQFInterlocks[1] = new QEpicsPV("BO-PS-QF:getHardwareInterlocks");
    this->pvQFInterlocks[2] = new QEpicsPV("BO-PS-QF:getSoftwareInterlocks");

    this->pvQDInterlocks[0] = new QEpicsPV("BO-PS-QD:getRegulationInterlocks");
    this->pvQDInterlocks[1] = new QEpicsPV("BO-PS-QD:getHardwareInterlocks");
    this->pvQDInterlocks[2] = new QEpicsPV("BO-PS-QD:getSoftwareInterlocks");

    this->pvState[0] = new QEpicsPV("BO-PS-BM:getState");
    this->pvState[1] = new QEpicsPV("BO-PS-QF:getState");
    this->pvState[2] = new QEpicsPV("BO-PS-QD:getState");
    for(int i = 0; i < 7; i++)
    {
        QObject::connect(this->pvBMInterlocks[i], SIGNAL(valueChanged(QVariant)), this, SLOT(interlocksChanged()));

        if(i < 3)
        {
            QObject::connect(this->pvQFInterlocks[i], SIGNAL(valueChanged(QVariant)), this, SLOT(interlocksChanged()));
            QObject::connect(this->pvQDInterlocks[i], SIGNAL(valueChanged(QVariant)), this, SLOT(interlocksChanged()));
            QObject::connect(this->pvState[i], SIGNAL(valueChanged(QVariant)), this, SLOT(statesChanged()));
        }

        // Booster correctors
        if(i < 6)
        {
            this->pvCR[i] = new QEpicsPV("BO-PS-CR" + QString::number(i+1) + ":getStatus");
            QObject::connect(this->pvCR[i], SIGNAL(valueChanged(QVariant)), this, SLOT(onCorrectorsChanged()));
        }
    }
}

FormBoosterPS::~FormBoosterPS()
{
    delete ui;
}

void FormBoosterPS::on_btnOpenCorrectors_clicked()
{
    this->correctors = new FormBoosterCorrectors;
    this->correctors->show();
}

void FormBoosterPS::on_btnOpenPulsed_clicked()
{
    this->pulsed = new FormBoosterPulsed;
    this->pulsed->show();
}

void FormBoosterPS::on_btnDisableTiming_clicked()
{
    Client::writePV("GBL-TI-EVR0-P1:enable", 0);
    Client::writePV("GBL-TI-EVR0-P2:enable", 0);
    Client::writePV("GBL-TI-EVR0-P3:enable", 0);
}

void FormBoosterPS::on_btnEnableTiming_clicked()
{
    Client::writePV("GBL-TI-EVR0-P1:enable", 1);
    Client::writePV("GBL-TI-EVR0-P2:enable", 1);
    Client::writePV("GBL-TI-EVR0-P3:enable", 1);
}

void FormBoosterPS::timingEnabled_Changed()
{
    if(this->pvTiming1->get().toInt() && this->pvTiming2->get().toInt() && this->pvTiming3->get().toInt())
    {
        this->ui->ledTimingEnabled->setValue(1);
    }
    else
        this->ui->ledTimingEnabled->setValue(0);
}

void FormBoosterPS::on_btnOpenDC_clicked()
{
    this->dc = new FormBoosterDCPower;
    this->dc->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, this->dc->size(), qApp->desktop()->availableGeometry()));
    this->dc->show();
}

void FormBoosterPS::on_btnStandby_clicked()
{
    Client::writePV("BO-PS-BM:enablePower", 0);
    Client::writePV("BO-PS-QF:enablePower", 0);
    Client::writePV("BO-PS-QD:enablePower", 0);
}

void FormBoosterPS::on_btnPowerOn_clicked()
{
    Client::writePV("BO-PS-BM:enablePower", 1);
    Client::writePV("BO-PS-BM:enablePulse", 0);
    Client::writePV("BO-PS-QF:enablePower", 1);
    Client::writePV("BO-PS-QF:enablePulse", 0);
    Client::writePV("BO-PS-QD:enablePower", 1);
    Client::writePV("BO-PS-QD:enablePulse", 0);
}

void FormBoosterPS::on_btnPulseOn_clicked()
{
    Client::writePV("BO-PS-BM:enablePulse", 1);
    Client::writePV("BO-PS-QF:enablePulse", 1);
    Client::writePV("BO-PS-QD:enablePulse", 1);
}

void FormBoosterPS::on_cbTrigger_currentIndexChanged(int index)
{
    if(index == 1)
    {
        Client::writePV("BO-PS-BM:setTriggerMask", (int) TRIGGER_OFF);
        Client::writePV("BO-PS-QF:setTriggerMask", (int) TRIGGER_OFF);
        Client::writePV("BO-PS-QD:setTriggerMask", (int) TRIGGER_OFF);
    }
    else if(index == 2)
    {
        Client::writePV("BO-PS-BM:setTriggerMask", (unsigned) TRIGGER_CONTINUOUS);
        Client::writePV("BO-PS-QF:setTriggerMask", (unsigned) TRIGGER_CONTINUOUS);
        Client::writePV("BO-PS-QD:setTriggerMask", (unsigned) TRIGGER_CONTINUOUS);
    }
}

void FormBoosterPS::on_btnBMLocks_clicked()
{
    this->bmInterlocks = new FormBMInterlocks;
    showUI(bmInterlocks);
}

void FormBoosterPS::on_btnQFLocks_clicked()
{
    this->dcInterlocks = new FormDCInterlocks("QF");
    showUI(dcInterlocks);
}

void FormBoosterPS::on_btnQDLocks_clicked()
{
    this->dcInterlocks = new FormDCInterlocks("QD");
    showUI(dcInterlocks);
}

void FormBoosterPS::interlocksChanged()
{
    bool value = false;
    for(int i = 0; i < 7; i++)
        value |= (this->pvBMInterlocks[i]->get().toInt() > 0);
    this->ui->ledBMLocks->setValue(value);

    value = false;
    for(int i = 0; i < 3; i++)
        value |= (this->pvQFInterlocks[i]->get().toInt() > 0);
    this->ui->ledQFLocks->setValue(value);

    value = false;
    for(int i = 0; i < 3; i++)
        value |= (this->pvQDInterlocks[i]->get().toInt() > 0);
    this->ui->ledQDLocks->setValue(value);
}

void FormBoosterPS::statesChanged()
{
    int stand = 0;
    int power = 0;
    int pulse = 0;
    int value = 0;
    for(int i = 0; i < 3; i++)
    {
        value = this->pvState[i]->get().toInt();
        if(value == 8 || value == 9)
            pulse++;
        else if(value == 6 || value == 7)
            power++;
        else if(value == 2)
            stand++;
    }

    switch(pulse)
    {
    case 0:
        ui->ledPulseON->setValue(0);
        ui->ledPulseON->setColour0Property(QColor::fromRgb(20, 60, 20));
        break;
    case 1:
    case 2:
        ui->ledPulseON->setValue(0);
        ui->ledPulseON->setColour0Property(QColor::fromRgb(240, 240, 5));
        break;
    case 3:
        ui->ledPulseON->setValue(0);
        ui->ledPulseON->setColour0Property(QColor::fromRgb(5, 240, 5));
        break;
    default:
        break;
    }

    switch(power)
    {
    case 0:
        ui->ledPowerON->setValue(0);
        ui->ledPowerON->setColour0Property(QColor::fromRgb(20, 60, 20));
        break;
    case 1:
    case 2:
        ui->ledPowerON->setValue(0);
        ui->ledPowerON->setColour0Property(QColor::fromRgb(240, 240, 5));
        break;
    case 3:
        ui->ledPowerON->setValue(0);
        ui->ledPowerON->setColour0Property(QColor::fromRgb(5, 240, 5));
        break;
    default:
        break;
    }

    switch(stand)
    {
    case 0:
        ui->ledStandby->setValue(0);
        ui->ledStandby->setColour0Property(QColor::fromRgb(20, 60, 20));
        break;
    case 1:
    case 2:
        ui->ledStandby->setValue(0);
        ui->ledStandby->setColour0Property(QColor::fromRgb(240, 240, 5));
        break;
    case 3:
        ui->ledStandby->setValue(0);
        ui->ledStandby->setColour0Property(QColor::fromRgb(5, 240, 5));
        break;
    default:
        break;
    }
}

void FormBoosterPS::onCorrectorsChanged()
{
    uint32_t value;
    for(int i = 0; i < 6; i++)
    {
        value = this->pvCR[i]->get().toInt();
        if(value == 1)
            this->findChild<QSimpleShape*>("ledCR_" + QString::number(i))->setValue(1);
        else if(value == 2 || value == 3)
            this->findChild<QSimpleShape*>("ledCR_" + QString::number(i))->setValue(2);
        else
            this->findChild<QSimpleShape*>("ledCR_" + QString::number(i))->setValue(0);
    }
}

void FormBoosterPS::on_btnOFF_clicked()
{
    Client::writePV("BO-PS-BM:setTriggerMask", (int) TRIGGER_OFF);
    Client::writePV("BO-PS-QF:setTriggerMask", (int) TRIGGER_OFF);
    Client::writePV("BO-PS-QD:setTriggerMask", (int) TRIGGER_OFF);
}

void FormBoosterPS::on_btnCont_clicked()
{
    Client::writePV("BO-PS-BM:setTriggerMask", (unsigned) TRIGGER_CONTINUOUS);
    Client::writePV("BO-PS-QF:setTriggerMask", (unsigned) TRIGGER_CONTINUOUS);
    Client::writePV("BO-PS-QD:setTriggerMask", (unsigned) TRIGGER_CONTINUOUS);
}
