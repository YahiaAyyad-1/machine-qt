#include "FormSrmThales.h"
#include "ui_FormSrmThales.h"

FormSrmThales::FormSrmThales(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormSrmThales)
{
    ui->setupUi(this);
    CONNECT_CLOSE_BUTTON;
}

FormSrmThales::~FormSrmThales()
{
    delete ui;
}
