#include "FormInjectionEfficiency.h"
#include "ui_FormInjectionEfficiency.h"

FormInjectionEfficiency::FormInjectionEfficiency(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormInjectionEfficiency)
{

    ui->setupUi(this);
    CONNECT_CLOSE_BUTTON;
}

FormInjectionEfficiency::~FormInjectionEfficiency()
{
    delete ui;
}
