#include "FormDCInterlocks.h"
#include "ui_FormDCInterlocks.h"

FormDCInterlocks::FormDCInterlocks(QString magnet, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormDCInterlocks)
{
    ui->setupUi(this);
    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));

    this->magnet = magnet;
    this->setWindowTitle("Booster " + this->magnet + " Interlocks");

    QESimpleShape* led;
    for(int i = 0; i < 16; i++)
    {
        led = this->findChild<QESimpleShape*>(QString("ledHard_%1").arg(i+1));
        led->setVariableNameProperty(QString::asprintf("BO-PS-%s:getHardwareInterlocks.B%X", this->magnet.toStdString().c_str(), i));

        if(i < 5)
        {
            led = this->findChild<QESimpleShape*>(QString("ledSoft_%1").arg(i+1));
            led->setVariableNameProperty(QString::asprintf("BO-PS-%s:getSoftwareInterlocks.B%X", this->magnet.toStdString().c_str(), i));
        }

        if(i < 7)
        {
            led = this->findChild<QESimpleShape*>(QString("ledReg_%1").arg(i+1));
            led->setVariableNameProperty(QString::asprintf("BO-PS-%s:getRegulationInterlocks.B%X", this->magnet.toStdString().c_str(), i));
        }
    }

    this->ui->btnReset->setVariableNameProperty(QString("BO-PS-%1:reset").arg(this->magnet));
}

FormDCInterlocks::~FormDCInterlocks()
{
    delete ui;
}
