#include "formsetcurrent.h"
#include "ui_formsetcurrent.h"

FormSetCurrent::FormSetCurrent(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormSetCurrent)
{
    ui->setupUi(this);
}

FormSetCurrent::~FormSetCurrent()
{
    delete ui;
}

void FormSetCurrent::on_btnClose_clicked()
{
    this->close();
}

