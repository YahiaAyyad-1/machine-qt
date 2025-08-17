#include "FormCoolingPressure.h"
#include "ui_FormCoolingPressure.h"

FormCoolingPressure::FormCoolingPressure(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormCoolingPressure)
{
    ui->setupUi(this);
    CONNECT_CLOSE_BUTTON;
}

FormCoolingPressure::~FormCoolingPressure()
{
    delete ui;
}
