#include "FormMainPowerDetails.h"
#include "ui_FormMainPowerDetails.h"

FormMainPowerDetails::FormMainPowerDetails(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormMainPowerDetails)
{
    ui->setupUi(this);

    ui->ltDevice->insertWidget(1, new power_meter_widget("1", "SR-MDB", "SR-MDB"));
    ui->ltDevice->insertWidget(2, new power_meter_widget("2", "RF-MDB", "SR-RF-MDB"));
}

FormMainPowerDetails::~FormMainPowerDetails()
{
    delete ui;
}
