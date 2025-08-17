#include "FormSRShaker.h"
#include "ui_FormSRShaker.h"

FormSRShaker::FormSRShaker(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormSRShaker)
{
    ui->setupUi(this);
}

FormSRShaker::~FormSRShaker()
{
    delete ui;
}

void FormSRShaker::on_btnClose_clicked()
{
    close();
}

void FormSRShaker::on_btnDetailsCH1_clicked()
{
    this->ilk = new FormShakerInterlocks("SR-DI-SHK1-CH1");
    this->ilk->show();
}

void FormSRShaker::on_btnDetailsCH2_clicked()
{
    this->ilk = new FormShakerInterlocks("SR-DI-SHK1-CH2");
    this->ilk->show();
}

void FormSRShaker::on_btnONCH1_clicked()
{

}
