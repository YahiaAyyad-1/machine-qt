#include "ion_pump_widget.h"
#include "ui_ion_pump_widget.h"

IonPumpWidget::IonPumpWidget(QString group, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IonPumpWidget)
{
    ui->setupUi(this);
    this->group = group;
    SET_GROUP(QELabel);

    this->enabled = new QEpicsPV(this->group + ":isEnabled");
    QObject::connect(this->enabled, SIGNAL(valueChanged(QVariant)), this, SLOT(pumpEnabledChanged(QVariant)));
    ui->ledEnabled->setToolTip(this->enabled->pv());
}

IonPumpWidget::~IonPumpWidget()
{
    delete ui;
}

void IonPumpWidget::pumpEnabledChanged(QVariant value)
{
    ui->ledEnabled->setValue( value.toString() == "YES" );
}
