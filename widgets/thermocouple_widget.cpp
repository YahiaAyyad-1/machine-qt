#include "thermocouple_widget.h"
#include "ui_thermocouple_widget.h"

ThermocoupleWidget::ThermocoupleWidget(QString name, QString prefix, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ThermocoupleWidget)
{
    ui->setupUi(this);
    this->prefix = prefix;

    ui->lblName->setText(name);
    ui->ledInterlock->setVariableNameSubstitutionsProperty("prefix=" + this->prefix);
    ui->txtSetpoint->setVariableNameSubstitutionsProperty("prefix=" + this->prefix);

    if(name.startsWith("RF-CR")) {
        this->prefix = "SR-" + name.replace("-AIR-", ":").replace("IN", "getAirInTemp").replace("OUT", "getAirOutTemp");
        ui->lblTemperature->setVariableNameProperty(this->prefix);
    }
    else
        ui->lblTemperature->setVariableNameSubstitutionsProperty("prefix=" + this->prefix);
}

ThermocoupleWidget::~ThermocoupleWidget()
{
    delete ui;
}
