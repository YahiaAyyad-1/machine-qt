#include "FormCurrentLimit.h"
#include "ui_FormCurrentLimit.h"

FormCurrentLimit::FormCurrentLimit(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormCurrentLimit)
{
    ui->setupUi(this);
    CONNECT_CLOSE_BUTTON;
}

FormCurrentLimit::~FormCurrentLimit()
{
    delete ui;
}
