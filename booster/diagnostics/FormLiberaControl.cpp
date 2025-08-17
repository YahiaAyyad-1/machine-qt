#include "FormLiberaControl.h"
#include "ui_FormLiberaControl.h"

FormLiberaControl::FormLiberaControl(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormLiberaControl)
{
    ui->setupUi(this);
    connect(ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
}

FormLiberaControl::~FormLiberaControl()
{
    delete ui;
}
