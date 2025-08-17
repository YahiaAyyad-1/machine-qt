#include "FormBeamlines.h"
#include "ui_FormBeamlines.h"

FormBeamlines::FormBeamlines(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormBeamlines)
{
    ui->setupUi(this);

    QString pvNames[BL_VALVES_COUNT] = {
        "FE08-VA-GV1",  "FE08-VA-PHSH", "FE08-VA-PHST",
        "D02C01-VA-ABS",
        "I09FE-VA-GV1", "I09FE-VA-PSH", "I09FE-PSS-PHST"
    };

    for(int i = 0; i < BL_VALVES_COUNT; i++)
    {
        this->pvs[2 * i] = new QEpicsPV(pvNames[i] + ":isClosed");
        this->pvs[2 * i + 1] = new QEpicsPV(pvNames[i] + ":isOpen");

        QObject::connect(this->pvs[2 * i], SIGNAL(valueChanged(QVariant)), this, SLOT(valveStateChanged()));
        QObject::connect(this->pvs[2 * i + 1], SIGNAL(valueChanged(QVariant)), this, SLOT(valveStateChanged()));
    }

    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
}

FormBeamlines::~FormBeamlines()
{
    delete ui;
}

void FormBeamlines::valveStateChanged()
{
    QSimpleShape* led;
    for(int i = 0; i < BL_VALVES_COUNT; i++)
    {
        led = this->findChild<QSimpleShape*>("ledStatus_" + NUMBER(i + 1));
        led->setValue(0);
        if(this->pvs[2 * i]->get().toInt() == 1)
            led->setColour0Property(Qt::yellow);
        else if(this->pvs[2 * i + 1]->get().toInt() == 1)
            led->setColour0Property(Qt::green);
        else
            led->setColour0Property(Qt::darkGreen);
    }
}

void FormBeamlines::on_btnInterlocks_clicked()
{
    this->interlocks = new FormBeamlinesInterlocks;
    showUI(this->interlocks);
}

void FormBeamlines::on_btnReset_clicked()
{
    Client::writePV("FE08-VA-GV1:reset",  1U);
    Client::writePV("FE08-VA-PHSH:reset", 1U);
    Client::writePV("FE08-VA-PHST:reset", 1U);
    Client::writePV("D02C01-VA-ABS:reset", 1U);
    Client::writePV("I09FE-VA-GV:resetInterlock", 1U);
}
