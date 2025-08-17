#include "FormBoosterPulsed.h"
#include "ui_FormBoosterPulsed.h"

FormBoosterPulsed::FormBoosterPulsed(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormBoosterPulsed)
{
    ui->setupUi(this);

    this->pvKickerVoltage = new QEpicsPV("BO-PS-EXK:getVoltage");
    QObject::connect(this->pvKickerVoltage, SIGNAL(valueChanged(QVariant)), this, SLOT(kickerVoltage_Changed()));
    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
}

FormBoosterPulsed::~FormBoosterPulsed()
{
    delete ui;
}

void FormBoosterPulsed::kickerVoltage_Changed()
{
    double voltage = this->pvKickerVoltage->get().toDouble();
    this->ui->lblKick->setText(QString::number(voltage * 1000.0 * 2.12299e-5) + " mrad");
}
