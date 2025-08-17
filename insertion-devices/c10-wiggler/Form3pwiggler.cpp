#include "Form3pwiggler.h"
#include "ui_Form3pwiggler.h"

Form3pwiggler::Form3pwiggler(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Form3pwiggler)
{
    ui->setupUi(this);
    CONNECT_CLOSE_BUTTON;

    this->pvMotor1Enable = new QEpicsPV("BEATS-WIGGLER:Phase-A-Relay");
    this->pvMotor2Enable = new QEpicsPV("BEATS-WIGGLER:Phase-B-Relay");
    this->pvEmergency1 = new QEpicsPV("BEATS-WIGGLER:Emergency-Switch-A-1");
    this->pvEmergency2 = new QEpicsPV("BEATS-WIGGLER:Emergency-Switch-A-2");
    this->pvEmergency3 = new QEpicsPV("BEATS-WIGGLER:Emergency-Switch-B-1");
    this->pvEmergency4 = new QEpicsPV("BEATS-WIGGLER:Emergency-Switch-B-2");
    QObject::connect(this->pvMotor1Enable, SIGNAL(valueChanged(QVariant)), this, SLOT(motorsEnableLed()));
    QObject::connect(this->pvMotor2Enable, SIGNAL(valueChanged(QVariant)), this, SLOT(motorsEnableLed()));
    QObject::connect(this->pvEmergency1, SIGNAL(valueChanged(QVariant)), this, SLOT(emergency1()));
    QObject::connect(this->pvEmergency2, SIGNAL(valueChanged(QVariant)), this, SLOT(emergency1()));
    QObject::connect(this->pvEmergency3, SIGNAL(valueChanged(QVariant)), this, SLOT(emergency2()));
    QObject::connect(this->pvEmergency4, SIGNAL(valueChanged(QVariant)), this, SLOT(emergency2()));

    this->current = new QEpicsPV("SRC01-DI-DCCT1:getDcctCurrent");
    this->energy = new QEpicsPV("SR-DI:getBeamEnergy");
    this->getGap = new QEpicsPV("ID10R01-MC1:I.RBV");
    this->setGap = new QEpicsPV("ID10R01-MC1:setGap");
    this->machineStatus = new QEpicsPV("Machine:Status");
    this->id10Status = new QEpicsPV("ID10:Status");
}

Form3pwiggler::~Form3pwiggler()
{
    delete ui;
}

void Form3pwiggler::on_btnStop_clicked()
{
    Client::writePV("ID10R01-MC1:I.STOP", 1);
    Client::writePV("ID10R01-MC1:J.STOP", 1);
}

void Form3pwiggler::on_btnDetailsY1_clicked()
{
    this->easyPS = new CaenEasyPSWindow("ID10-PS-Y1");
    showUI(easyPS);
}


void Form3pwiggler::on_btnDetailsY2_clicked()
{
    this->easyPS = new CaenEasyPSWindow("ID10-PS-Y2");
    showUI(easyPS);
}


void Form3pwiggler::on_btnMotion_clicked()
{
    this->galil = new FormGalilController("ID10R01-MC1", "A,B,,,,,,", "I,J,,,,,,");
    showUI(galil);
}


void Form3pwiggler::on_btnDetailsX1_clicked()
{
    this->fastPS = new CaenFastPSWindow("ID10-PS-X1");
    showUI(fastPS);
}


void Form3pwiggler::on_btnDetailsX2_clicked()
{
    this->fastPS = new CaenFastPSWindow("ID10-PS-X2");
    showUI(fastPS);
}

void Form3pwiggler::motorsEnableLed()
{
    int motor1 = this->pvMotor1Enable->get().toInt();
    int motor2 = this->pvMotor2Enable->get().toInt();

    if (motor1 == 1 && motor2 == 1)
    {
        ui->ledMotors->setValue(1);
    }
    else
    {
        ui->ledMotors->setValue(0);
    }

}

void Form3pwiggler::emergency1()
{
    int _emergency1 = this->pvEmergency1->get().toInt();
    int _emergency2 = this->pvEmergency2->get().toInt();

    if (_emergency1 == 1 && _emergency2 == 1)
    {
        ui->lefEmergency1->setValue(1);
    }
    else
    {
        ui->lefEmergency1->setValue(0);
    }

}

void Form3pwiggler::emergency2()
{
    int _emergency3 = this->pvEmergency3->get().toInt();
    int _emergency4 = this->pvEmergency4->get().toInt();

    if (_emergency3 == 1 && _emergency4 == 1)
    {
        ui->lefEmergency2->setValue(1);
    }
    else
    {
        ui->lefEmergency2->setValue(0);
    }

}


void Form3pwiggler::on_btnAlarmsReset_clicked()
{
    Client::writePV("BEATS-WIGGLER:reset", 1);
    QThread::sleep(2);
    Client::writePV("BEATS-WIGGLER:reset", 0);

}

void Form3pwiggler::on_btnSwitchesReset_clicked()
{
    Client::writePV("BEATS-WIGGLER:reset", 1);
    QThread::sleep(2);
    Client::writePV("BEATS-WIGGLER:reset", 0);
}

//void Form3pwiggler::on_btnMov_clicked()
//{
//    double get_current = current->get().toDouble();
//    double get_energy = energy->get().toDouble();
//    double get_Gap = getGap->get().toDouble();
//    double set_Gap = setGap->get().toDouble();
//    int get_id10_status = id10Status->get().toInt();
//    int get_machine_status = machineStatus->get().toInt();


//    if(set_Gap < get_Gap)
//    {
//        if(get_current > 2.0 && get_energy > 2.499 && get_id10_status == 0)
//        {
//            if(get_machine_status == 3 || get_machine_status == 6 || get_machine_status == 7 || get_machine_status == 2)
//            {
//                QProcess* p1 = new QProcess;
//                p1->start("gnome-terminal --geometry 100x30 -x ssh root@10.2.0.22 \"beats-ff\"");
//                Client::writePV("ID10:Status", 1);
//            }

//        }
//    }
//}

