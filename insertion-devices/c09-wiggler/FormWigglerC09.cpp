#include "FormWigglerC09.h"
#include "ui_FormWigglerC09.h"

FormWigglerC09::FormWigglerC09(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormWigglerC09)
{
    ui->setupUi(this);
    CONNECT_CLOSE_BUTTON;

    this->pvLimits[0] = new QEpicsPV("ID09R01-MC1:A.HLS");
    this->pvLimits[1] = new QEpicsPV("ID09R01-MC1:A.LLS");
    this->pvLimits[2] = new QEpicsPV("ID09R01-MC1:B.HLS");
    this->pvLimits[3] = new QEpicsPV("ID09R01-MC1:B.LLS");
    this->pvLimits[4] = new QEpicsPV("ID09R01-MC1:I.HLS");
    this->pvLimits[5] = new QEpicsPV("ID09R01-MC1:I.LLS");
    this->current = new QEpicsPV("SRC01-DI-DCCT1:getDcctCurrent");
    this->energy = new QEpicsPV("SR-DI:getBeamEnergy");
    this->getGap = new QEpicsPV("ID09R01-MC1:I.RBV");
    this->setGap = new QEpicsPV("ID09R01-MC1:setGap");
    this->machineStatus = new QEpicsPV("Machine:Status");
    this->id9Status = new QEpicsPV("ID09:Status");

    for(int i = 0; i < 6; i++)
        QObject::connect(pvLimits[i], SIGNAL(valueChanged(QVariant&)), this, SLOT(onLimitsChanged()));
}

FormWigglerC09::~FormWigglerC09()
{
    delete ui;
}

void FormWigglerC09::on_btnMotion_clicked()
{
    this->galil = new FormGalilController("ID09R01-MC1", "A,B,C,D,E,F,G,H", "I,J,K,L,M,N,O,P");
    showUI(galil);
}

void FormWigglerC09::on_btnON_clicked()
{
    Client::writePV("ID09-PS-VL:Enable", 1);
    Client::writePV("ID09-PS-HL:Enable", 1);
    Client::writePV("ID09-PS-VS:Enable", 1);
    Client::writePV("ID09-PS-HS:Enable", 1);
    Client::writePV("ID09-PS-SQ:Enable", 1);
}

void FormWigglerC09::on_btnOFF_clicked()
{
    Client::writePV("ID09-PS-VL:Enable", 0);
    Client::writePV("ID09-PS-HL:Enable", 0);
    Client::writePV("ID09-PS-VS:Enable", 0);
    Client::writePV("ID09-PS-HS:Enable", 0);
    Client::writePV("ID09-PS-SQ:Enable", 0);
}

void FormWigglerC09::on_btnDetails1_clicked()
{
    this->fastPS = new CaenFastPSWindow("ID09-PS-VL");
    showUI(fastPS);
}

void FormWigglerC09::on_btnDetails2_clicked()
{
    this->easyPS = new CaenEasyPSWindow("ID09-PS-HL");
    showUI(easyPS);
}

void FormWigglerC09::on_pushButton_5_clicked()
{
    this->easyPS = new CaenEasyPSWindow("ID09-PS-VS");
    showUI(easyPS);
}

void FormWigglerC09::on_pushButton_6_clicked()
{
    this->easyPS = new CaenEasyPSWindow("ID09-PS-HS");
    showUI(easyPS);
}

void FormWigglerC09::on_pushButton_7_clicked()
{
    this->easyPS = new CaenEasyPSWindow("ID09-PS-SQ");
    showUI(easyPS);
}

void FormWigglerC09::on_btnStop_clicked()
{
    Client::writePV("ID09R01-MC1:I.STOP", 1);
    Client::writePV("ID09R01-MC1:J.STOP", 1);
}

void FormWigglerC09::onLimitsChanged()
{
    for(int i = 0; i < 6; i++) {
        if(pvLimits[i]->get().toInt()) {
            ui->ledLimits->setValue(0);
            break;
        }
    }

    ui->ledLimits->setValue(1);
}

//void FormWigglerC09::on_btnMov_clicked()
//{
//    double get_current = current->get().toDouble();
//    double get_energy = energy->get().toDouble();
//    double get_Gap = getGap->get().toDouble();
//    double set_Gap = setGap->get().toDouble();
//    int get_id9_status = id9Status->get().toInt();
//    int get_machine_status = machineStatus->get().toInt();

//    if(set_Gap < get_Gap)
//    {
//        if(get_current > 2.0 && get_energy > 2.499 && get_id9_status == 0)
//        {
//            if(get_machine_status == 3 || get_machine_status == 6 || get_machine_status == 7 || get_machine_status == 2)
//            {
//                QProcess* p1 = new QProcess;
//                p1->start("gnome-terminal --geometry 100x30 -x ssh root@10.2.0.22 \"ms-tcs-ff\"");
//                Client::writePV("ID09:Status", 1);
//            }
//        }
//    }
//}

