#include "FormShaker.h"
#include "ui_FormShaker.h"

FormShaker::FormShaker(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormShaker)
{
    ui->setupUi(this);
    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));

    for(int i = 0; i < 6; i++)
    {
        this->shakerInterlocks[i] = new QEpicsPV(this->interlockPVs[i]);
        QObject::connect(this->shakerInterlocks[i], SIGNAL(valueChanged(QVariant)), this, SLOT(interlockStatus_Changed()));
    }
}

FormShaker::~FormShaker()
{
    delete ui;
}

void FormShaker::interlockStatus_Changed()
{
    this->ui->ledInterlock1->setValue( this->shakerInterlocks[0]->get().toBool() &&
                                       this->shakerInterlocks[1]->get().toBool() &&
                                       this->shakerInterlocks[2]->get().toBool());

    this->ui->ledInterlock2->setValue( this->shakerInterlocks[3]->get().toBool() &&
                                       this->shakerInterlocks[4]->get().toBool() &&
                                       this->shakerInterlocks[5]->get().toBool());
}

void FormShaker::on_btnDetails1_clicked()
{
    this->ilk = new FormShakerInterlocks("BO-DI-SHK1-CH1");
    this->ilk->show();
}

void FormShaker::on_btnDetails2_clicked()
{
    this->ilk = new FormShakerInterlocks("BO-DI-SHK1-CH2");
    this->ilk->show();
}
