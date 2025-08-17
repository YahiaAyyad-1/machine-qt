#include "FormGeneralControl.h"
#include "ui_FormGeneralControl.h"

FormGeneralControl::FormGeneralControl(QString magnet, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormGeneralControl)
{
    ui->setupUi(this);

    this->magnet = magnet;
    this->setWindowTitle(this->magnet + " General Control");
    this->ui->txtStart->setVariableNameProperty(QString("SR-PS-SEQ:set%1WaveformStart").arg(this->magnet));
    this->ui->txtCycle->setVariableNameProperty(QString("SR-PS-SEQ:set%1WaveformCycle").arg(this->magnet));
    this->ui->txtReference->setVariableNameProperty(QString("SR-PS-SEQ:set%1Current").arg(this->magnet));

    int gw = 0;
    int ch = 0;
    if(this->magnet == "QF")
    {
        for(gw = 0; gw <= 3; gw++)
        {
            for(ch = 0; ch <= 14; ch += 2)
            {
                this->sequences.push_back(new QEpicsPV(QString::asprintf("SR-PS-GW%d-CH%d:getStateSequencer", gw, ch)));
                this->states.push_back(new QEpicsPV(QString::asprintf("SR-PS-GW%d-CH%d:getStateHandler", gw, ch)));
                this->modes.push_back(new QEpicsPV(QString::asprintf("SR-PS-GW%d-CH%d:getMode", gw, ch)));
            }
        }
    }
    else if(this->magnet == "QD")
    {
        for(gw = 0; gw <= 3; gw++)
        {
            for(ch = 1; ch <= 15; ch += 2)
            {
                this->sequences.push_back(new QEpicsPV(QString::asprintf("SR-PS-GW%d-CH%d:getStateSequencer", gw, ch)));
                this->states.push_back(new QEpicsPV(QString::asprintf("SR-PS-GW%d-CH%d:getStateHandler", gw, ch)));
                this->modes.push_back(new QEpicsPV(QString::asprintf("SR-PS-GW%d-CH%d:getMode", gw, ch)));
            }
        }
    }
    else if(this->magnet == "SF")
    {
        this->sequences.push_back(new QEpicsPV("SR-PS-GW4-CH12:getStateSequencer"));
        this->sequences.push_back(new QEpicsPV("SR-PS-GW4-CH14:getStateSequencer"));
        this->states.push_back(new QEpicsPV("SR-PS-GW4-CH12:getStateHandler"));
        this->states.push_back(new QEpicsPV("SR-PS-GW4-CH14:getStateHandler"));
        this->modes.push_back(new QEpicsPV("SR-PS-GW4-CH12:getMode"));
        this->modes.push_back(new QEpicsPV("SR-PS-GW4-CH14:getMode"));
    }
    else if(this->magnet == "SD")
    {
        this->sequences.push_back(new QEpicsPV("SR-PS-GW4-CH13:getStateSequencer"));
        this->sequences.push_back(new QEpicsPV("SR-PS-GW4-CH15:getStateSequencer"));
        this->states.push_back(new QEpicsPV("SR-PS-GW4-CH13:getStateHandler"));
        this->states.push_back(new QEpicsPV("SR-PS-GW4-CH15:getStateHandler"));
        this->modes.push_back(new QEpicsPV("SR-PS-GW4-CH13:getMode"));
        this->modes.push_back(new QEpicsPV("SR-PS-GW4-CH15:getMode"));
    }

    foreach (QEpicsPV* pv, this->states)
        QObject::connect(pv, SIGNAL(valueChanged(QVariant)), this, SLOT(stateHandlersChanged()));
    foreach (QEpicsPV* pv, this->modes)
        QObject::connect(pv, SIGNAL(valueChanged(QVariant)), this, SLOT(modesChanged()));
    foreach (QEpicsPV* pv, this->sequences)
        QObject::connect(pv, SIGNAL(valueChanged(QVariant)), this, SLOT(sequencersChanged()));

    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
    this->tuning = NULL;
    this->waveforms = NULL;
    this->parameters = NULL;
}

FormGeneralControl::~FormGeneralControl()
{
    delete ui;
}

void FormGeneralControl::sendCommand(int command)
{
    int gw = 0;
    int ch = 0;
    if(this->magnet == "QF")
    {
        for(gw = 0; gw <= 3; gw++)
        {
            for(ch = 0; ch <= 14; ch += 2)
                Client::writePV(QString::asprintf("SR-PS-GW%d-CH%d:setCommand", gw, ch), command);
        }
    }
    else if(this->magnet == "QD")
    {
        for(gw = 0; gw <= 3; gw++)
        {
            for(ch = 1; ch <= 15; ch += 2)
                Client::writePV(QString::asprintf("SR-PS-GW%d-CH%d:setCommand", gw, ch), command);
        }
    }
    else if(this->magnet == "SF")
    {
        Client::writePV("SR-PS-GW4-CH12:setCommand", command);
        Client::writePV("SR-PS-GW4-CH14:setCommand", command);
    }
    else if(this->magnet == "SD")
    {
        Client::writePV("SR-PS-GW4-CH13:setCommand", command);
        Client::writePV("SR-PS-GW4-CH15:setCommand", command);
    }
    else
        return;
}

void FormGeneralControl::on_btnOpenloop_clicked()
{
    sendCommand(COMMAND_OPEN);
}

void FormGeneralControl::on_btnOFF_clicked()
{
    sendCommand(COMMAND_OFF);
}

void FormGeneralControl::on_btnStandby_clicked()
{
    sendCommand(COMMAND_STANDBY);
}

void FormGeneralControl::on_btnON_clicked()
{
    sendCommand(COMMAND_ON);
}

void FormGeneralControl::on_btnReset_clicked()
{
    sendCommand(COMMAND_RESET);
}

void FormGeneralControl::on_btnSemiauto_clicked()
{
    sendCommand(COMMAND_SEMI_A);
}

void FormGeneralControl::on_Auto_clicked()
{
    sendCommand(COMMAND_AUTO);
}

void FormGeneralControl::on_Manual_clicked()
{
    sendCommand(COMMAND_MANUAL);
}

void FormGeneralControl::on_btnTrigger_clicked()
{
    sendCommand(COMMAND_TRIGGER);
}

void FormGeneralControl::on_btnPause_clicked()
{
    sendCommand(COMMAND_PAUSE);
}

void FormGeneralControl::on_btnResume_clicked()
{
    sendCommand(COMMAND_RESUME);
}

void FormGeneralControl::on_btnStop_clicked()
{
    sendCommand(COMMAND_STOP);
}

void FormGeneralControl::setMode(int mode)
{
    int gw = 0;
    int ch = 0;
    if(this->magnet == "QF")
    {
        for(gw = 0; gw <= 3; gw++)
        {
            for(ch = 0; ch <= 14; ch += 2)
                Client::writePV(QString::asprintf("SR-PS-GW%d-CH%d:setMode", gw, ch), mode);
        }
    }
    else if(this->magnet == "QD")
    {
        for(gw = 0; gw <= 3; gw++)
        {
            for(ch = 1; ch <= 15; ch += 2)
                Client::writePV(QString::asprintf("SR-PS-GW%d-CH%d:setMode", gw, ch), mode);
        }
    }
    else if(this->magnet == "SF")
    {
        Client::writePV("SR-PS-GW4-CH12:setMode", mode);
        Client::writePV("SR-PS-GW4-CH14:setMode", mode);
    }
    else if(this->magnet == "SD")
    {
        Client::writePV("SR-PS-GW4-CH13:setMode", mode);
        Client::writePV("SR-PS-GW4-CH15:setMode", mode);
    }
    else
        return;
}

void FormGeneralControl::on_btnDC_clicked()
{
    setMode(MODE_DC);
}

void FormGeneralControl::on_btnWaveform_clicked()
{
    setMode(MODE_WAVEFORM);
}

void FormGeneralControl::stateHandlersChanged()
{
    int offCount = 0;
    int onCount  = 0;
    int openCount = 0;
    int standbyCount = 0;
    int value = 0;

    foreach (QEpicsPV* pv, this->states)
    {
        value = pv->get().toInt();
        if(value == STATE_OFF)
            offCount++;
        if(value == STATE_STANDBY)
            standbyCount++;
        if(value == STATE_ON)
            onCount++;
        if(value == STATE_OPEN)
            openCount++;
    }

    if(offCount == 0)
        this->ui->ledOFF->setValue(0);
    else if(offCount > 0 && offCount < this->states.size())
    {
        this->ui->ledOFF->setLedType(QSimpleShape::Warning);
        this->ui->ledOFF->setValue(1);
    }
    else if(offCount == this->states.size())
    {
        this->ui->ledOFF->setLedType(QSimpleShape::Status);
        this->ui->ledOFF->setValue(1);
    }

    if(onCount == 0)
        this->ui->ledON->setValue(0);
    else if(onCount > 0 && onCount < this->states.size())
    {
        this->ui->ledON->setLedType(QSimpleShape::Warning);
        this->ui->ledON->setValue(1);
    }
    else if(onCount == this->states.size())
    {
        this->ui->ledON->setLedType(QSimpleShape::Status);
        this->ui->ledON->setValue(1);
    }

    if(standbyCount == 0)
        this->ui->ledStandby->setValue(0);
    else if(standbyCount > 0 && standbyCount < this->states.size())
    {
        this->ui->ledStandby->setLedType(QSimpleShape::Warning);
        this->ui->ledStandby->setValue(1);
    }
    else if(standbyCount == this->states.size())
    {
        this->ui->ledStandby->setLedType(QSimpleShape::Status);
        this->ui->ledStandby->setValue(1);
    }

    if(openCount == 0)
        this->ui->ledOpen->setValue(0);
    else if(openCount > 0 && openCount < this->states.size())
    {
        this->ui->ledOpen->setLedType(QSimpleShape::Warning);
        this->ui->ledOpen->setValue(1);
    }
    else if(openCount == this->states.size())
    {
        this->ui->ledOpen->setLedType(QSimpleShape::Status);
        this->ui->ledOpen->setValue(1);
    }
}

void FormGeneralControl::modesChanged()
{
    int waveCount = 0;
    int dcCount  = 0;
    int value = 0;

    foreach (QEpicsPV* pv, this->modes)
    {
        value = pv->get().toInt();
        if(value == MODE_DC)
            dcCount++;
        if(value == MODE_WAVEFORM)
            waveCount++;
    }

    if(dcCount == 0)
        this->ui->ledDC->setValue(0);
    else if(dcCount > 0 && dcCount < this->modes.size())
    {
        this->ui->ledDC->setLedType(QSimpleShape::Warning);
        this->ui->ledDC->setValue(1);
    }
    else if(dcCount == this->modes.size())
    {
        this->ui->ledDC->setLedType(QSimpleShape::Status);
        this->ui->ledDC->setValue(1);
    }

    if(waveCount == 0)
        this->ui->ledWave->setValue(0);
    else if(waveCount > 0 && waveCount < this->modes.size())
    {
        this->ui->ledWave->setLedType(QSimpleShape::Warning);
        this->ui->ledWave->setValue(1);
    }
    else if(waveCount == this->modes.size())
    {
        this->ui->ledWave->setLedType(QSimpleShape::Status);
        this->ui->ledWave->setValue(1);
    }
}

void FormGeneralControl::sequencersChanged()
{
    int semiCount = 0;
    int autoCount = 0;
    int manualCount = 0;
    int value = 0;

    foreach (QEpicsPV* pv, this->sequences)
    {
        value = pv->get().toInt();
        if(value == SEQUENCE_SEMIAUTO || value == SEQUENCE_SEMIAUTO_A)
            semiCount++;
        if(value == SEQUENCE_AUTO || value == SEQUENCE_AUTO_A)
            autoCount++;
        if(value == SEQUENCE_MANUAL || value == SEQUENCE_MANUAL)
            manualCount++;
    }

    if(semiCount == 0)
        this->ui->ledSemiAuto->setValue(0);
    else if(semiCount > 0 && semiCount < this->sequences.size())
    {
        this->ui->ledSemiAuto->setLedType(QSimpleShape::Warning);
        this->ui->ledSemiAuto->setValue(1);
    }
    else if(semiCount == this->sequences.size())
    {
        this->ui->ledSemiAuto->setLedType(QSimpleShape::Status);
        this->ui->ledSemiAuto->setValue(1);
    }

    if(autoCount == 0)
        this->ui->ledAuto->setValue(0);
    else if(autoCount > 0 && autoCount < this->sequences.size())
    {
        this->ui->ledAuto->setLedType(QSimpleShape::Warning);
        this->ui->ledAuto->setValue(1);
    }
    else if(autoCount == this->sequences.size())
    {
        this->ui->ledAuto->setLedType(QSimpleShape::Status);
        this->ui->ledAuto->setValue(1);
    }

    if(manualCount == 0)
        this->ui->ledManual->setValue(0);
    else if(manualCount > 0 && manualCount < this->sequences.size())
    {
        this->ui->ledManual->setLedType(QSimpleShape::Warning);
        this->ui->ledManual->setValue(1);
    }
    else if(manualCount == this->sequences.size())
    {
        this->ui->ledManual->setLedType(QSimpleShape::Status);
        this->ui->ledManual->setValue(1);
    }
}

void FormGeneralControl::on_btnTuning_clicked()
{
    OPEN_UI(this->tuning, FormGeneralTuning, this->magnet, this);
}

void FormGeneralControl::on_btnWaveforms_clicked()
{
    OPEN_UI(this->waveforms, FormGeneralWaveform, this->magnet, this);
}

void FormGeneralControl::on_btnFirmware_clicked()
{
    OPEN_UI(this->parameters, FormGeneralParameters, this->magnet, this);
}

void FormGeneralControl::on_btnInterlock_clicked()
{
    sendCommand(COMMAND_FAULT);
}
