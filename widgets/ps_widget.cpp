#include "ps_widget.h"
#include "ui_ps_widget.h"

PowerSupplyWidget::PowerSupplyWidget(QString prefix, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PowerSupplyWidget)
{
    ui->setupUi(this);
    this->prefix = prefix;

    ui->lblGroup->setText(this->prefix);
    ui->lblCurrent->setVariableNameSubstitutionsProperty("group=" + this->prefix);
    ui->lblVoltage->setVariableNameSubstitutionsProperty("group=" + this->prefix);
    ui->txtCurrent->setVariableNameSubstitutionsProperty("group=" + this->prefix);
    ui->lblState->setVariableNameSubstitutionsProperty("group=" + this->prefix);

    ui->btnDetails->setToolTip(this->prefix + " - Details");
    ui->ledSequence->setToolTip(this->prefix);
    ui->ledState->setToolTip(this->prefix);

    this->pvStateHandler = new QEpicsPV(this->prefix + ":getStateHandler", this);
    this->pvStateSequencer = new QEpicsPV(this->prefix + ":getStateSequencer", this);
    this->pvMode = new QEpicsPV(this->prefix + ":getMode", this);
    this->machineMode = new QEpicsPV("Machine:Status", this);
    this->pvGetCurrent = new QEpicsPV(this->prefix + ":getIload", this);
    this->pvSetCurrent = new QEpicsPV(this->prefix + ":setReference", this);
    QObject::connect(this->pvStateHandler, SIGNAL(valueChanged(QVariant)), this, SLOT(onStateHandlerChanged(QVariant)));
    QObject::connect(this->pvStateSequencer, SIGNAL(valueChanged(QVariant)), this, SLOT(onStateSequencerChanged(QVariant)));
    QObject::connect(this->pvMode, SIGNAL(valueChanged(QVariant)), this, SLOT(onModeChanged(QVariant)));
    QObject::connect(this->machineMode, SIGNAL(valueChanged(QVariant)), this, SLOT(onMachineStateChanged(QVariant)));
    QObject::connect(this->pvGetCurrent, SIGNAL(valueChanged(QVariant)), this, SLOT(onCurrentValueChanged(QVariant)));
    this->details = NULL;
}

PowerSupplyWidget::~PowerSupplyWidget()
{
    delete ui;
}

void PowerSupplyWidget::onStateHandlerChanged(QVariant value)
{
    int state = value.toInt();
    this->psState = state;
    ui->ledState->setValue( state == STATE_FAULT || state == STATE_TRANSIENT );
}

void PowerSupplyWidget::onStateSequencerChanged(QVariant value)
{
    int sequence = value.toInt();
    if(sequence == SEQUENCE_SEMIAUTO_ACTIVE || sequence == SEQUENCE_AUTO_ACTIVE || sequence == SEQUENCE_MANUAL_ACTIVE)
        ui->ledSequence->setValue(0);
    else if(sequence == SEQUENCE_SEMIAUTO || sequence == SEQUENCE_AUTO || sequence == SEQUENCE_MANUAL)
        ui->ledSequence->setValue(1);
    else if(sequence == SEQUENCE_DC)
        ui->ledSequence->setValue(2);
    else
        ui->ledSequence->setValue(3);
}

void PowerSupplyWidget::on_btnDetails_clicked()
{
    OPEN_UI(this->details, uiSRPowerSupplyDetails, this->prefix, this);
}

void PowerSupplyWidget::onModeChanged(QVariant value)
{
    this->psMode = value.toInt();
}

void PowerSupplyWidget::onMachineStateChanged(QVariant value)
{
    bool condition = value.toInt() != 3 && value.toInt() != 6 && value.toInt() != 7;
    ui->txtCurrent->setEnabled(condition);
}

void PowerSupplyWidget::onCurrentValueChanged(QVariant value)
{
    double set_value = pvSetCurrent->get().toDouble();
    double get_value = value.toDouble();
    if(std::abs(get_value - set_value) > 0.1)
    {
        ui->lblCurrent->setStyleSheet(LABEL_ALARM_QSS);
    }
    else
    {
        ui->lblCurrent->setStyleSheet(LABEL_DEFAULT_QSS);
    }
}
