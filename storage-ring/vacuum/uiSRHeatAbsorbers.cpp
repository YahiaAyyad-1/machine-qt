#include "uiSRHeatAbsorbers.h"
#include "ui_uiSRHeatAbsorbers.h"

uiSRHeatAbsorbers::uiSRHeatAbsorbers(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::uiSRHeatAbsorbers)
{
    ui->setupUi(this);
}

uiSRHeatAbsorbers::~uiSRHeatAbsorbers()
{
    delete ui;
}

void uiSRHeatAbsorbers::on_btnClose_clicked()
{
    close();
}
