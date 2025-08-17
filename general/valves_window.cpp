#include "valves_window.h"
#include "ui_valves_window.h"

ValvesWindow::ValvesWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ValvesWindow)
{
    ui->setupUi(this);
    CONNECT_CLOSE_BUTTON;

    ui->ltTL1->addWidget(new ValveWidget("TL1-VA-GV1", false, this));
    ui->ltTL1->addWidget(new ValveWidget("TL1-VA-GV2", false, this));
    ui->ltBooster->addWidget(new ValveWidget("BOC02-VA-GV1", false, this));
    ui->ltBooster->addWidget(new ValveWidget("BOC03-VA-GV1", false, this));
    ui->ltBooster->addWidget(new ValveWidget("BOC05-VA-GV1", false, this));
    ui->ltTL2->addWidget(new ValveWidget("TL2-VA-GV1", false, this));
    ui->ltTL2->addWidget(new ValveWidget("TL2-VA-GV2", false, this));
    ui->ltTL2->addWidget(new ValveWidget("TL2-VA-SH1", true, this));

    for(int cell = 1; cell <= 15; cell += 2) {
        ui->ltRing->addWidget(new ValveWidget(QString::asprintf("SRC%02d-VA-GV1", cell), false, this));
        ui->ltRing->addWidget(new ValveWidget(QString::asprintf("SRC%02d-VA-GV2", cell), false, this));
        if(cell == 13)
            ui->ltRing->addWidget(new ValveWidget(QString::asprintf("SRC14-VA-GV"), false, this));
    }
    ui->ltRing->addWidget(new ValveWidget(QString::asprintf("SRC16-VA-PHC-GV"), false, this));

    this->machineStatus = new QEpicsPV("Machine:Status");
    QObject::connect(this->machineStatus, SIGNAL(valueChanged(const QVariant&)), this, SLOT(onMachineStatusValueChanged(const QVariant&)));
}

ValvesWindow::~ValvesWindow()
{
    delete ui;
}

void ValvesWindow::on_btnReset_clicked()
{
    QString prefix;
    QList<ValveWidget*> widgets = this->findChildren<ValveWidget*>();
    ui->btnReset->setEnabled(false);
    for(auto widget : widgets) {
        prefix = widget->getPrefix();
        Client::writePV(prefix + ":reset", 1);
    }
    ui->btnReset->setEnabled(true);
}


void ValvesWindow::on_btnOpenAll_clicked()
{
    QString prefix;
    QList<ValveWidget*> widgets = this->findChildren<ValveWidget*>();
    ui->btnOpenAll->setEnabled(false);
    for(auto widget : widgets) {
        prefix = widget->getPrefix();
        Client::writePV(prefix + ":setOpen", 1);
    }
    ui->btnOpenAll->setEnabled(true);
}


void ValvesWindow::on_btnCloseAll_clicked()
{
    QString prefix;
    QList<ValveWidget*> widgets = this->findChildren<ValveWidget*>();
    ui->btnCloseAll->setEnabled(false);
    for(auto widget : widgets) {
        prefix = widget->getPrefix();
        Client::writePV(prefix + ":setClose", 1);
    }
    ui->btnCloseAll->setEnabled(true);
}

void ValvesWindow::onMachineStatusValueChanged(const QVariant &status)
{
    const int machine_dev = 1;
    const int user_beam = 3;
    const int free_mode = 6;
    const int beamline_dev = 7;

    int current_status = status.toUInt();

    if (current_status == machine_dev || current_status == user_beam ||
        current_status == free_mode || current_status == beamline_dev)
    {
        this->ui->btnCloseAll->setEnabled(false);
    } else
    {
        this->ui->btnCloseAll->setEnabled(true);
    }
}
