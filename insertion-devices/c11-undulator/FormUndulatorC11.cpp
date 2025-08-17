#include "FormUndulatorC11.h"
#include "ui_FormUndulatorC11.h"
#include "client.h"
#include <QProcess>

FormUndulatorC11::FormUndulatorC11(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormUndulatorC11)
{

    ui->setupUi(this);
    this->stopStatus = new QEpicsPV("UE56IS:BaseCmnUsrStop.RVAL");
//    QObject::connect(this->stopStatus, SIGNAL(valueInited(QVariant)), this, SLOT(stop_btn_on_start()));
//    QObject::connect(ui->btnStopShift, SIGNAL(clicked()), this, SLOT(on_btnStop_clicked()));
    CONNECT_CLOSE_BUTTON;
}

FormUndulatorC11::~FormUndulatorC11()
{
    delete ui;
}

void FormUndulatorC11::on_btnHC1Details_clicked()
{
    this->easyPS = new CaenEasyPSWindow("ID11-PS-HC1");
    showUI(easyPS);
}

void FormUndulatorC11::on_btnVC1Details_clicked()
{
    this->easyPS = new CaenEasyPSWindow("ID11-PS-VC1");
    showUI(easyPS);
}

void FormUndulatorC11::on_btnHC2Details_clicked()
{
    this->easyPS = new CaenEasyPSWindow("ID11-PS-HC2");
    showUI(easyPS);
}

void FormUndulatorC11::on_btnVC2Details_clicked()
{
    this->easyPS = new CaenEasyPSWindow("ID11-PS-VC2");
    showUI(easyPS);
}

void FormUndulatorC11::on_btnON_clicked()
{
    Client::writePV("ID11-PS-HC1:Enable", 1);
    Client::writePV("ID11-PS-VC1:Enable", 1);
    Client::writePV("ID11-PS-HC2:Enable", 1);
    Client::writePV("ID11-PS-VC2:Enable", 1);
}

void FormUndulatorC11::on_btnOFF_clicked()
{
    Client::writePV("ID11-PS-HC1:Enable", 0);
    Client::writePV("ID11-PS-VC1:Enable", 0);
    Client::writePV("ID11-PS-HC2:Enable", 0);
    Client::writePV("ID11-PS-VC2:Enable", 0);
}




//void FormUndulatorC11::on_btnStop_clicked()
//{
//    int stop_status = this->stopStatus->get().toInt();
//    if(stop_status == 0)
//    {
//        Client::writePV("UE56IS:BaseCmnUsrStop",1);
//        ui->btnStop->setStyleSheet("background-color : #FF0000;");
//        ui->btnStop->setText("STOPPED");
//        ui->btnStopShift->setStyleSheet("background-color : #FF0000;");
//        ui->btnStopShift->setText("STOPPED");
//    }
//    else
//    {
//        Client::writePV("UE56IS:BaseCmnUsrStop",0);
//        ui->btnStop->setStyleSheet("background-color : #00FF00;");
//        ui->btnStop->setText("STOP");
//        ui->btnStopShift->setStyleSheet("background-color : #00FF00;");
//        ui->btnStopShift->setText("STOP");
//    }
//}

//void FormUndulatorC11::stop_btn_on_start()
//{
//    int stop_status_val = this->stopStatus->get().toInt();
//    if(stop_status_val == 1)
//     {
//        ui->btnStop->setStyleSheet("background-color : #FF0000;");
//        ui->btnStop->setText("STOPPED");
//        ui->btnStopShift->setStyleSheet("background-color : #FF0000;");
//        ui->btnStopShift->setText("STOPPED");
//    }
//    else
//    {
//        ui->btnStop->setStyleSheet("background-color : #00FF00;");
//        ui->btnStop->setText("STOP");
//        ui->btnStopShift->setStyleSheet("background-color : #00FF00;");
//        ui->btnStopShift->setText("STOP");
//    }
//}




