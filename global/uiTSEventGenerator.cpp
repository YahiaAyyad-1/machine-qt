#include "uiTSEventGenerator.h"
#include "ui_uiTSEventGenerator.h"

uiTSEventGenerator::uiTSEventGenerator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::uiTSEventGenerator)
{
    ui->setupUi(this);
}

uiTSEventGenerator::~uiTSEventGenerator()
{
    delete ui;
}

void uiTSEventGenerator::on_btnClose_clicked()
{
    close();
}
