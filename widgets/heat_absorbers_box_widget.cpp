#include "heat_absorbers_box_widget.h"
#include "ui_heat_absorbers_box_widget.h"

HeatAbsorbersBoxWidget::HeatAbsorbersBoxWidget(QString config, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HeatAbsorbersBoxWidget)
{
    ui->setupUi(this);

    QStringList subItems;
    QStringList items = config.split(' ');
    ui->groupBox->setTitle(items[0].replace('-', ' '));
    for (int i = 1; i < items.size(); i++) {
        subItems = items[i].split('|');
        ui->layout->addWidget(new HeatAbsorberWidget(subItems[0], subItems[1]), (i - 1) / 2, (i - 1) % 2);
    }
}

HeatAbsorbersBoxWidget::~HeatAbsorbersBoxWidget()
{
    delete ui;
}
