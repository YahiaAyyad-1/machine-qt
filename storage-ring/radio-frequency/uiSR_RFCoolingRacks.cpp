#include "uiSR_RFCoolingRacks.h"
#include "ui_uiSR_RFCoolingRacks.h"

uiSR_RFCoolingRacks::uiSR_RFCoolingRacks(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::uiSR_RFCoolingRacks)
{
    ui->setupUi(this);
    this->machineMode = new QEpicsPV("Machine:Status", this);
    QObject::connect(this->machineMode, SIGNAL(valueChanged(QVariant)), this, SLOT(onMachineStateChanged(QVariant)));
    QObject::connect(this->machineMode, SIGNAL(valueInited(QVariant)), this, SLOT(onMachineStateChanged(QVariant)));

}

uiSR_RFCoolingRacks::~uiSR_RFCoolingRacks()
{
    delete ui;
}

void uiSR_RFCoolingRacks::on_btnClose_clicked()
{
    close();
}

void uiSR_RFCoolingRacks::onMachineStateChanged(QVariant value)
{
    bool condition = value.toInt() != 3;

    ui->btnOffCav1->setEnabled(condition);
    ui->btnOffCav2->setEnabled(condition);
    ui->btnOffCav3->setEnabled(condition);
    ui->btnOffCav4->setEnabled(condition);
}
