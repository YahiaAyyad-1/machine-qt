#include "FormBMInterlocks.h"
#include "ui_FormBMInterlocks.h"

FormBMInterlocks::FormBMInterlocks(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormBMInterlocks)
{
    ui->setupUi(this);
    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));

    QESimpleShape* led;
    for(int i = 0; i < 42; i++)
    {
        led = this->findChild<QESimpleShape*>(QString("ledHard_%1").arg(i+1));
        if(i >= 0 && i < 14)
            led->setVariableNameProperty(QString::asprintf("BO-PS-BM:getMasterHardwareInterlocks.B%X", i));
        else if(i >= 14 && i < 28)
            led->setVariableNameProperty(QString::asprintf("BO-PS-BM:getSlave1HardwareInterlocks.B%X", i - 14));
        else
            led->setVariableNameProperty(QString::asprintf("BO-PS-BM:getSlave2HardwareInterlocks.B%X", i - 28));
    }

    for(int i = 0; i < 7; i++)
    {
        led = this->findChild<QESimpleShape*>(QString("ledReg_%1").arg(i+1));
        led->setVariableNameProperty(QString::asprintf("BO-PS-BM:getRegulationInterlocks.B%X", i));
    }
}

FormBMInterlocks::~FormBMInterlocks()
{
    delete ui;
}
