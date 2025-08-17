#include "heat_absorber_widget.h"
#include "ui_heat_absorber_widget.h"

HeatAbsorberWidget::HeatAbsorberWidget(QString pvName, QString text, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HeatAbsorberWidget)
{
    ui->setupUi(this);

    ui->ledInterlock->setVariableNameProperty(pvName);
    ui->label->setText(text);


}

HeatAbsorberWidget::~HeatAbsorberWidget()
{
    delete ui;
}
