#include "corrector_ps_widget.h"
#include "ui_corrector_ps_widget.h"

CorrectorPowerSupplyWidget::CorrectorPowerSupplyWidget(QString prefix, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CorrectorPowerSupplyWidget)
{
    ui->setupUi(this);
    this->prefix = prefix;

    ui->lblGroup->setText(this->prefix);
    ui->lblCurrent->setVariableNameSubstitutionsProperty("group=" + this->prefix);
    ui->txtCurrent->setVariableNameSubstitutionsProperty("group=" + this->prefix);
    ui->lblState->setVariableNameSubstitutionsProperty("group=" + this->prefix);
    ui->btnOFF->setVariableNameSubstitutionsProperty("group=" + this->prefix);
    ui->btnON->setVariableNameSubstitutionsProperty("group=" + this->prefix);

    this->pvState = new QEpicsPV(this->prefix + ":getStateHandler");
    this->pvFaults = new QEpicsPV(this->prefix + ":getFaults");
    this->pvGetCurrent = new QEpicsPV(this->prefix + ":getIload", this);
    this->pvSetCurrent = new QEpicsPV(this->prefix + ":setReference", this);
    this->machineMode = new QEpicsPV("Machine:Status", this);

    QObject::connect(this->pvState, SIGNAL(valueChanged(QVariant)), this, SLOT(onStateHandlerChanged(QVariant)));
    QObject::connect(this->pvFaults, SIGNAL(valueChanged(QVariant)), this, SLOT(onFaultsChanged(QVariant)));
    QObject::connect(this->pvGetCurrent, SIGNAL(valueChanged(QVariant)), this, SLOT(onCurrentValueChanged(QVariant)));
    QObject::connect(this->machineMode, SIGNAL(valueChanged(QVariant)), this, SLOT(onMachineStateChanged(QVariant)));
    QObject::connect(this->machineMode, SIGNAL(valueInited(QVariant)), this, SLOT(onMachineStateChanged(QVariant)));



    this->details = NULL;
}

CorrectorPowerSupplyWidget::~CorrectorPowerSupplyWidget()
{
    delete ui;
}

void CorrectorPowerSupplyWidget::onStateHandlerChanged(QVariant value)
{
    int state = value.toInt();
    ui->ledOFF->setValue( state == 1 );
    ui->ledON->setValue( state == 2 );
    ui->ledOFF->setToolTip("State Handler: " + STRING(state));
    ui->ledON->setToolTip("State Handler: " + STRING(state));
}

void CorrectorPowerSupplyWidget::onFaultsChanged(QVariant value)
{
    QList<int> warnings({0x32, 0x37, 0x38, 0x46, 0x47, 0x4a});
    int fault = value.toInt() & 0xFF;
    if(fault >= 0x0 && fault <= 0xE1) {
        if(fault == 0)
            ui->ledFault->setValue(0);
        else if(warnings.contains(fault))
            ui->ledFault->setValue(1);
        else
            ui->ledFault->setValue(2);
    }
    else
        ui->ledFault->setValue(0);

    ui->ledFault->setToolTip("getFaults: " + STRING(fault));
}

void CorrectorPowerSupplyWidget::on_btnDetails_clicked()
{
    OPEN_UI(this->details, FormCorrectorDetails, this->prefix, this);
}

QString CorrectorPowerSupplyWidget::getPrefix()
{
    return this->prefix;
}

void CorrectorPowerSupplyWidget::onCurrentValueChanged(QVariant value)
{
    double set_value = pvSetCurrent->get().toDouble();
    double get_value = value.toDouble();
    if(std::abs(get_value - set_value) > 0.05)
    {
        ui->lblCurrent->setStyleSheet("border:2px solid red ;");
    }
    else
    {
        ui->lblCurrent->setStyleSheet("");
    }
}

void CorrectorPowerSupplyWidget::onMachineStateChanged(QVariant value)
{
    bool condition = value.toInt() != 3 && value.toInt() != 6 && value.toInt() != 7;
    ui->txtCurrent->setEnabled(condition);
    ui->btnON->setEnabled(condition);
    ui->btnOFF->setEnabled(condition);
}
