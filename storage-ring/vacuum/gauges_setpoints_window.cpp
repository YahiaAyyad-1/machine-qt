#include "gauges_setpoints_window.h"
#include "ui_gauges_setpoints_window.h"

GaugesSetpointsWindow::GaugesSetpointsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GaugesSetpointsWindow)
{
    ui->setupUi(this);
    CONNECT_CLOSE_BUTTON;

    int gc = 1;
    int gauges = 0;
    QString imgPrefix;
    for(int cell = 1; cell <= 16; cell++) {
        if(cell == 3) {
            gauges = 5;
            gc = 2;
        }
        else if(cell % 2 == 0)
            gauges = 1;
        else
            gauges = 2;

        for (int i = 1; i <= gauges; i++) {
            imgPrefix = QString::asprintf("SRC%02d-VA-IMG%d", cell, i);
            if(i == 5)
                ui->layout->addWidget(new GaugeSetpointWidget(imgPrefix, 1, 4, false));
            else if(cell == 4)
                ui->layout->addWidget(new GaugeSetpointWidget(imgPrefix, 1, 5, false));
            else
                ui->layout->addWidget(new GaugeSetpointWidget(imgPrefix, gc, cell % 2 == 0 ? 3 : i, gc != 1));
            if(i == 4)
                gc++;
        }

        if(cell >= 6 && cell % 2 == 0)
            gc++;
    }
}

GaugesSetpointsWindow::~GaugesSetpointsWindow()
{
    delete ui;
}
