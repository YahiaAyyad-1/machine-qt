#include "sr_cooling_window.h"
#include "ui_sr_cooling_window.h"

RingCoolingWindow::RingCoolingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RingCoolingWindow)
{
    ui->setupUi(this);

    int cell, row, column;
    for(int i = 0; i < 16; i++) {
        cell = i + 1;
        row = i / 8;
        column = i % 8;

        ui->ltBoxes->addWidget(new RingCoolingBoxWidget(cell, this), row, column);
    }

    QObject::connect(ui->btnClose, SIGNAL(clicked()), this, SLOT(close()));

    this->thc = NULL;
    this->heat = NULL;
    this->pressure = NULL;

    this->pvHAB = new QEpicsPV("SR-VA-HAB:isInterlock");
    QObject::connect(this->pvHAB, &QEpicsPV::valueChanged,
                     this, [this](const QVariant & value) {
        QString style;
        style = (value.toUInt() == 0) ? "background-color: red" : "background-color: lightgreen";
        this->ui->btnHeatAbsorbers->setDefaultStyle(style);
    });
}

RingCoolingWindow::~RingCoolingWindow()
{
    delete ui;
}

void RingCoolingWindow::on_btnReset_clicked()
{
    for(int i = 1; i <= 16; i++)
    {
        Client::writePV(QString::asprintf("SRC%02d-CO-SB:reset", i), 1);
    }

    Client::writePV("SRC03-RF-SSA1-DIS00:resetInterlocks", 1);
    Client::writePV("SRC03-RF-SSA2-DIS00:resetInterlocks", 1);
    Client::writePV("SRC03-RF-SSA3-DIS00:resetInterlocks", 1);
    Client::writePV("SRC03-RF-SSA4-DIS00:resetInterlocks", 1);
    Client::writePV("SRC-CO-SB-PON:reset", 1);
}

void RingCoolingWindow::on_btnThermoCouples_clicked()
{
    OPEN_UI(this->thc, FormCellsThermocouples, this);
}

void RingCoolingWindow::on_btnHeatAbsorbers_clicked()
{
    OPEN_UI(this->heat, HeatAbsorbersWindow, this);
}

void RingCoolingWindow::on_btnPressure_clicked()
{
    OPEN_UI(this->pressure, FormCoolingPressure, this);
}
