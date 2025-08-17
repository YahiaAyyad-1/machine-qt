#include "FormBeamlinesStatus.h"
#include "ui_FormBeamlinesStatus.h"

FormBeamlinesStatus::FormBeamlinesStatus(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormBeamlinesStatus)
{
    ui->setupUi(this);
    CONNECT_CLOSE_BUTTON;
}

FormBeamlinesStatus::~FormBeamlinesStatus()
{
    delete ui;
}
