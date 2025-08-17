#include "FormMasterOscillator.h"
#include "ui_FormMasterOscillator.h"

FormMasterOscillator::FormMasterOscillator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormMasterOscillator)
{
    ui->setupUi(this);
    QObject::connect(this->ui->btn_close, SIGNAL(clicked(bool)), this, SLOT(close()));
}

FormMasterOscillator::~FormMasterOscillator()
{
    delete ui;
}

void FormMasterOscillator::on_btnON_clicked()
{
    Client::writePV("BO-RF-SGN1:enable", 1);
    Client::writePV("BO-RF-SGN1:setFrequency", 499.674);
}
