#include "valve_widget.h"
#include "ui_valve_widget.h"

ValveWidget::ValveWidget(QString prefix, bool isPSSValve, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ValveWidget)
{
    ui->setupUi(this);

    this->prefix = prefix;
    ui->ledStatus->setVariableNameSubstitutionsProperty("group=" + prefix);
    ui->lblState->setVariableNameSubstitutionsProperty("group=" + prefix);
    ui->lblFault->setVariableNameSubstitutionsProperty("group=" + prefix);
    ui->btnClose->setVariableNameSubstitutionsProperty("group=" + prefix);
    ui->btnOpen->setVariableNameSubstitutionsProperty("group=" + prefix);
    ui->lblName->setText(prefix);
    ui->ledPSS->setVisible(isPSSValve);

    this->machineStatus = new QEpicsPV("Machine:Status");
    QObject::connect(this->machineStatus, SIGNAL(valueChanged(const QVariant&)), this, SLOT(onMachineStatusValueChanged(const QVariant&)));
}

ValveWidget::~ValveWidget()
{
    delete ui;
}

QString ValveWidget::getPrefix()
{
    return prefix;
}

void ValveWidget::onMachineStatusValueChanged(const QVariant &status)
{
    const int machine_dev = 1;
    const int user_beam = 3;
    const int free_mode = 6;
    const int beamline_dev = 7;

    int current_status = status.toUInt();

    if (current_status == machine_dev || current_status == user_beam ||
        current_status == free_mode || current_status == beamline_dev)
    {
        this->ui->btnClose->setEnabled(false);
    } else
    {
        this->ui->btnClose->setEnabled(true);
    }
}
