#include "sr_cooling_box_widget.h"
#include "ui_sr_cooling_box_widget.h"

RingCoolingBoxWidget::RingCoolingBoxWidget(int cell, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RingCoolingBoxWidget)
{
    ui->setupUi(this);

    ui->groupBox->setTitle("Cell " + QString::number(cell));
    for(QString device : devices) {
        ui->ltSwitches->insertWidget(ui->ltSwitches->count(), new RingCoolingSwitchWidget(cell, device, this));
    }
}

RingCoolingBoxWidget::~RingCoolingBoxWidget()
{
    delete ui;
}
