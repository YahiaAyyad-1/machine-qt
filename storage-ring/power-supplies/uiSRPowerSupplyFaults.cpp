#include "uiSRPowerSupplyFaults.h"
#include "ui_uiSRPowerSupplyFaults.h"

uiSRPowerSupplyFaults::uiSRPowerSupplyFaults(QString group, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::uiSRPowerSupplyFaults)
{
    ui->setupUi(this);
    this->group = group;

    CONNECT_CLOSE_BUTTON;
    SET_GROUP(QESimpleShape);
    SET_GROUP(QELabel);

    this->setWindowTitle(group + " - Faults");
}

uiSRPowerSupplyFaults::~uiSRPowerSupplyFaults()
{
    delete ui;
}

void uiSRPowerSupplyFaults::on_pushButton_clicked()
{
    this->expert = new FormFaultsExperts(this->group);
    showUI(expert);
}
