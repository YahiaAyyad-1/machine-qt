#include "FormBoosterCorrectors.h"
#include "ui_FormBoosterCorrectors.h"
#include "client.h"

FormBoosterCorrectors::FormBoosterCorrectors(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormBoosterCorrectors)
{
    ui->setupUi(this);
    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));

    for(int i = 1; i <= 6; i++)
    {
        QPushButton* off = this->findChild<QPushButton*>(QString("btnOFF_%1").arg(i));
        QObject::connect(off, SIGNAL(clicked(bool)), this, SLOT(enableButtons_Clicked()));

        QPushButton* on = this->findChild<QPushButton*>(QString("btnON_%1").arg(i));
        QObject::connect(on, SIGNAL(clicked(bool)), this, SLOT(enableButtons_Clicked()));
    }
}

FormBoosterCorrectors::~FormBoosterCorrectors()
{
    delete ui;
}


void FormBoosterCorrectors::enableButtons_Clicked()
{
    QPushButton* button = (QPushButton*) sender();
    QString name = button->objectName().split('_')[0];
    QString id = button->objectName().split('_')[1];
    QString pv = "BO-PS-CR%1:enable";

    if(name == "btnOFF")
    {
        Client::writePV(pv.arg(id), 0);
    }
    else if(name == "btnON")
    {
        Client::writePV(pv.arg(id), 1);
    }
}
