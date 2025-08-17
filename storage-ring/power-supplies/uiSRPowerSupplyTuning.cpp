#include "uiSRPowerSupplyTuning.h"
#include "ui_uiSRPowerSupplyTuning.h"

uiSRPowerSupplyTuning::uiSRPowerSupplyTuning(QString group, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::uiSRPowerSupplyTuning)
{
    ui->setupUi(this);
    this->group = group;
    this->setWindowTitle(group + " - Tuning");

    QObject::connect(this->ui->btnClose, SIGNAL(clicked()), this, SLOT(close()));
    SET_GROUP(QELabel);
    SET_GROUP(QENumericEdit);
}

uiSRPowerSupplyTuning::~uiSRPowerSupplyTuning()
{
    delete ui;
}
