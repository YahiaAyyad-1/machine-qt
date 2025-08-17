#include "uiTL2Cooling.h"
#include "ui_uiTL2Cooling.h"

uiTL2Cooling::uiTL2Cooling(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::uiTL2Cooling)
{
    ui->setupUi(this);
}

uiTL2Cooling::~uiTL2Cooling()
{
    delete ui;
}

void uiTL2Cooling::on_btnClose_clicked()
{
    close();
}

void uiTL2Cooling::on_btnReset_clicked()
{
    Client::writePV("TL2-CO-SB1:reset", "1");
    Client::writePV("TL2-CO-SB2:reset", "1");
}
