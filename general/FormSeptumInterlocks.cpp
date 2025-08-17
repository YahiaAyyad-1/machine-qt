#include "FormSeptumInterlocks.h"
#include "ui_FormSeptumInterlocks.h"

FormSeptumInterlocks::FormSeptumInterlocks(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormSeptumInterlocks)
{
    ui->setupUi(this);
    CONNECT_CLOSE_BUTTON;
}

FormSeptumInterlocks::~FormSeptumInterlocks()
{
    delete ui;
}
