#include "sr_correctors_window.h"
#include "ui_sr_correctors_window.h"

RingCorrectorsWindow::RingCorrectorsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RingCorrectorsWindow)
{
    ui->setupUi(this);
    QVBoxLayout* layout;
    for(int i = 1; i <= 16; i++) {
        if(i <= 8)
            layout = ui->ltCorrectors1;
        else
            layout = ui->ltCorrectors2;

        layout->insertWidget(ui->ltCorrectors1->count(), new CorrectorTitleWidget(i, this));
        layout->insertWidget(ui->ltCorrectors1->count(), new CorrectorPowerSupplyWidget(QString::asprintf("SRC%02d-PS-HC1", i), this));
        layout->insertWidget(ui->ltCorrectors1->count(), new CorrectorPowerSupplyWidget(QString::asprintf("SRC%02d-PS-VC1", i), this));
        if(i % 2 != 0)
            layout->insertWidget(ui->ltCorrectors1->count(), new CorrectorPowerSupplyWidget(QString::asprintf("SRC%02d-PS-SQ1", i), this));
        layout->insertWidget(ui->ltCorrectors1->count(), new CorrectorPowerSupplyWidget(QString::asprintf("SRC%02d-PS-VC2", i), this));
        layout->insertWidget(ui->ltCorrectors1->count(), new CorrectorPowerSupplyWidget(QString::asprintf("SRC%02d-PS-HC2", i), this));
    }

    this->machineMode = new QEpicsPV("Machine:Status", this);
    QObject::connect(this->machineMode, SIGNAL(valueChanged(QVariant)), this, SLOT(onMachineStateChanged(QVariant)));

    CONNECT_CLOSE_BUTTON;
}

RingCorrectorsWindow::~RingCorrectorsWindow()
{
    delete ui;
}

void RingCorrectorsWindow::on_btnOFF_H_clicked()
{
    for(CorrectorPowerSupplyWidget* w : this->findChildren<CorrectorPowerSupplyWidget*>()) {
        if(w->getPrefix().contains("HC"))
            Client::writePV(w->getPrefix() + ":setCommand", 0);
    }
}

void RingCorrectorsWindow::on_btnON_H_clicked()
{
    for(CorrectorPowerSupplyWidget* w : this->findChildren<CorrectorPowerSupplyWidget*>()) {
        if(w->getPrefix().contains("HC"))
            Client::writePV(w->getPrefix() + ":setCommand", 1);
    }
}

void RingCorrectorsWindow::on_btnOFF_V_clicked()
{
    for(CorrectorPowerSupplyWidget* w : this->findChildren<CorrectorPowerSupplyWidget*>()) {
        if(w->getPrefix().contains("VC"))
            Client::writePV(w->getPrefix() + ":setCommand", 0);
    }
}

void RingCorrectorsWindow::on_btnON_V_clicked()
{
    for(CorrectorPowerSupplyWidget* w : this->findChildren<CorrectorPowerSupplyWidget*>()) {
        if(w->getPrefix().contains("VC"))
            Client::writePV(w->getPrefix() + ":setCommand", 1);
    }
}

void RingCorrectorsWindow::on_btnOFF_S_clicked()
{
    for(CorrectorPowerSupplyWidget* w : this->findChildren<CorrectorPowerSupplyWidget*>()) {
        if(w->getPrefix().contains("SQ"))
            Client::writePV(w->getPrefix() + ":setCommand", 0);
    }
}

void RingCorrectorsWindow::on_btnON_S_clicked()
{
    for(CorrectorPowerSupplyWidget* w : this->findChildren<CorrectorPowerSupplyWidget*>()) {
        if(w->getPrefix().contains("SQ"))
            Client::writePV(w->getPrefix() + ":setCommand", 1);
    }
}

void RingCorrectorsWindow::onMachineStateChanged(QVariant value)
{
    bool condition = value.toInt() != 3 && value.toInt() != 6 && value.toInt() != 7;
    ui->btnOFF_H->setEnabled(condition);
    ui->btnOFF_S->setEnabled(condition);
    ui->btnOFF_V->setEnabled(condition);
    ui->btnON_H->setEnabled(condition);
    ui->btnON_S->setEnabled(condition);
    ui->btnON_V->setEnabled(condition);
}
