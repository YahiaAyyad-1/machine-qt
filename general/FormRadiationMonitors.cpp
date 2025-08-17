#include "FormRadiationMonitors.h"
#include "ui_FormRadiationMonitors.h"

FormRadiationMonitors::FormRadiationMonitors(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormRadiationMonitors)
{
    ui->setupUi(this);
    CONNECT_CLOSE_BUTTON;
}

FormRadiationMonitors::~FormRadiationMonitors()
{
    delete ui;
}
