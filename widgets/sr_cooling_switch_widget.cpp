#include "sr_cooling_switch_widget.h"
#include "ui_sr_cooling_switch_widget.h"

RingCoolingSwitchWidget::RingCoolingSwitchWidget(int cell, QString device, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RingCoolingSwitchWidget)
{
    ui->setupUi(this);

    this->prefix = QString::asprintf("SRC%02d-MA-", cell) + device;
    ui->lblDevice->setText(device);
    ui->ledFlow->setVariableNameSubstitutionsProperty("prefix=" + this->prefix);
    ui->ledTemperature->setVariableNameSubstitutionsProperty("prefix=" + this->prefix);
}

RingCoolingSwitchWidget::~RingCoolingSwitchWidget()
{
    delete ui;
}
