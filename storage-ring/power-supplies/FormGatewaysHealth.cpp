#include "FormGatewaysHealth.h"
#include "ui_FormGatewaysHealth.h"

FormGatewaysHealth::FormGatewaysHealth(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormGatewaysHealth)
{
    ui->setupUi(this);

    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
    for(int i = 0; i < 6; i++)
    {
        this->pvGwLoad[i] = new QEpicsPV(QString("SR-PS-GW%1:getLoad").arg(QString::number(i)));
        this->pvGwFreeRAM[i] = new QEpicsPV(QString("SR-PS-GW%1:getFreeRam").arg(QString::number(i)));

        QObject::connect(this->pvGwLoad[i], SIGNAL(valueChanged(QVariant)), this, SLOT(loadChanged()));
        QObject::connect(this->pvGwFreeRAM[i], SIGNAL(valueChanged(QVariant)), this, SLOT(freeRAMChanged()));
    }
}

FormGatewaysHealth::~FormGatewaysHealth()
{
    delete ui;
}

void FormGatewaysHealth::loadChanged()
{
    QSimpleShape* led;
    for(int i = 0; i < 6; i++)
    {
        led = this->findChild<QSimpleShape*>("ledStatus" + QString::number(i + 1));
        if(this->pvGwLoad[i]->get().toDouble() >= 0.5)
        {
            led->setValue(1);
            led->setColour1Property(Qt::red);
        }
        else
        {
            led->setValue(0);
            led->setColour0Property(Qt::green);
        }
    }
}

void FormGatewaysHealth::freeRAMChanged()
{
    QLabel* label;
    for(int i = 0; i < 6; i++)
    {
        label = this->findChild<QLabel*>("lblFreeRAM" + QString::number(i + 1));
        label->setText(QString::number(this->pvGwFreeRAM[i]->get().toDouble() / 1024.0 / 1024.0) + " MB");
    }
}
