#include "FormDCConfig.h"
#include "ui_FormDCConfig.h"

#define CONTINUOUS_MASK 1073741822U

FormDCConfig::FormDCConfig(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormDCConfig)
{
    ui->setupUi(this);

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

FormDCConfig::~FormDCConfig()
{
    delete ui;
}

void FormDCConfig::powerInterlocks_Changed()
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

    this->ui->ledBMInterlock->setValue( bmLock1 || bmLock2 || bmLock3 || bmLock4 || bmLock5 || bmLock6 || bmLock7 ? 1 : 0 );
    this->ui->ledQFInterlock->setValue( qfLock1 || qfLock2 || qfLock3 ? 1 : 0 );
    this->ui->ledQDInterlock->setValue( qdLock1 || qdLock2 || qdLock3 ? 1 : 0 );
}

void FormDCConfig::on_cbBMMask_currentIndexChanged(int index)
{
    switch (index)
    {
    case 0:
        break;
    case 1:
        Client::writePV("BO-PS-BM:setTriggerMask", 0);
        this->ui->cbBMMask->setCurrentIndex(0);
        break;
    case 2:
        Client::writePV("BO-PS-BM:setTriggerMask", CONTINUOUS_MASK);
        this->ui->cbBMMask->setCurrentIndex(0);
        break;
    }

    return;
}

void FormDCConfig::on_cbQFMask_currentIndexChanged(int index)
{
    switch (index)
    {
    case 0:
        break;
    case 1:
        Client::writePV("BO-PS-QF:setTriggerMask", 0);
        this->ui->cbBMMask->setCurrentIndex(0);
        break;
    case 2:
        Client::writePV("BO-PS-QF:setTriggerMask", CONTINUOUS_MASK);
        this->ui->cbBMMask->setCurrentIndex(0);
        break;
    }

    return;
}

void FormDCConfig::on_cbQDMask_currentIndexChanged(int index)
{
    switch (index)
    {
    case 0:
        break;
    case 1:
        Client::writePV("BO-PS-QD:setTriggerMask", 0);
        this->ui->cbBMMask->setCurrentIndex(0);
        break;
    case 2:
        Client::writePV("BO-PS-QD:setTriggerMask", CONTINUOUS_MASK);
        this->ui->cbBMMask->setCurrentIndex(0);
        break;
    }

    return;
}

void FormDCConfig::on_comboBox_currentIndexChanged(int index)
{
    switch(index)
    {
    case 0:
        break;
    case 1:
        this->dcWF = new FormDCWaveform("BM");
        this->dcWF->show();
        break;
    case 2:
        this->dcWF = new FormDCWaveform("QF");
        this->dcWF->show();
        break;
    case 3:
        this->dcWF = new FormDCWaveform("QD");
        this->dcWF->show();
        break;
    default:
        break;
    }

    this->ui->comboBox->setCurrentIndex(0);
    return;
}

void FormDCConfig::on_cbTuning_currentIndexChanged(int index)
{
    switch(index)
    {
    case 0:
        break;
    case 1:
        this->tune = new FormTunePI("BM");
        this->tune->show();
        break;
    case 2:
        this->tune = new FormTunePI("QF");
        this->tune->show();
        break;
    case 3:
        this->tune = new FormTunePI("QD");
        this->tune->show();
        break;
    default:
        break;
    }

    this->ui->cbTuning->setCurrentIndex(0);
    return;
}
