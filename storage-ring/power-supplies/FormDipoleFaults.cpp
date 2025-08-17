#include "FormDipoleFaults.h"
#include "ui_FormDipoleFaults.h"

FormDipoleFaults::FormDipoleFaults(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormDipoleFaults)
{
    ui->setupUi(this);
    CONNECT_CLOSE_BUTTON;
}

FormDipoleFaults::~FormDipoleFaults()
{
    delete ui;
}

void FormDipoleFaults::on_btnExpert_clicked()
{
    this->expert = new FormDipoleFaultsExpert;
    showUI(expert);
}
