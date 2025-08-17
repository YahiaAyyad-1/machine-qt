#include "uiSRGaugeInterlocks.h"
#include "ui_uiSRGaugeInterlocks.h"

uiSRGaugeInterlocks::uiSRGaugeInterlocks(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::uiSRGaugeInterlocks)
{
    ui->setupUi(this);
}

uiSRGaugeInterlocks::~uiSRGaugeInterlocks()
{
    delete ui;
}

void uiSRGaugeInterlocks::on_btnClose_clicked()
{
    close();
}
