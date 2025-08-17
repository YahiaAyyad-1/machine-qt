#include "uiTL2Vacuum.h"
#include "ui_uiTL2Vacuum.h"

uiTL2Vacuum::uiTL2Vacuum(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::uiTL2Vacuum)
{
    ui->setupUi(this);
    connect(ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));

    for(int i = 0; i < 8; i++)
    {
        this->pvStatus[i] = new QEpicsPV(QString("TL2-VA-IP%1:isEnabled").arg(QString::number(i+1)));
        QObject::connect(pvStatus[i], SIGNAL(valueChanged(QVariant)), this, SLOT(onStatusChanged()));
    }

    valves = NULL;
}

uiTL2Vacuum::~uiTL2Vacuum()
{
    delete ui;
}

void uiTL2Vacuum::on_btnValves_clicked()
{
    OPEN_UI(valves, ValvesWindow, this);
}

void uiTL2Vacuum::onStatusChanged()
{
    for(int i = 0; i < 8; i++)
    {
        QSimpleShape* led = this->findChild<QSimpleShape*>("ledIP_" + QString::number(i));
        if(this->pvStatus[i]->get().toString() == "YES")
            led->setValue(1);
        else
            led->setValue(0);
    }
}

void uiTL2Vacuum::on_btnReset_clicked()
{
    ui->btnReset->setEnabled(false);
    for(int i = 0; i < 24; i++)
    {
        Client::writePV(this->pvs[i] + ":reset", 1);
    }
    ui->btnReset->setEnabled(true);
}
