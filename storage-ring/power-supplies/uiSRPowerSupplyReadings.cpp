#include "uiSRPowerSupplyReadings.h"
#include "ui_uiSRPowerSupplyReadings.h"

#include "client.h"

uiSRPowerSupplyReadings::uiSRPowerSupplyReadings(QString group, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::uiSRPowerSupplyReadings)
{
    ui->setupUi(this);

    this->group = group;
    QObject::connect(ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
    SET_GROUP(QELabel);
    ui->btnClear->setVariableNameSubstitutionsProperty("group=" + this->group);

    this->setWindowTitle(this->group + " - Readings");
}

uiSRPowerSupplyReadings::~uiSRPowerSupplyReadings()
{
    delete ui;
}

void uiSRPowerSupplyReadings::on_pushButton_clicked()
{
    Client::writePV(this->group + ":setEmax", "0");
}
