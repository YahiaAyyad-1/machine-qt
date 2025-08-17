#include "tl1_correctors_window.h"
#include "ui_tl1_correctors_window.h"

TL1CorrectorsWindow::TL1CorrectorsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TL1CorrectorsWindow)
{
    ui->setupUi(this);
    for(int i = 1; i <= 4; i++) {
        if(i > 1) {
            if(i == 4)
                ui->ltCorrectors->addWidget( new CaenPowerSupplyWidget(QString("TL1-PS-CR%1-X").arg(i), true, this) );
            else
                ui->ltCorrectors->addWidget( new CaenPowerSupplyWidget(QString("TL1-PS-CR%1-X").arg(i), false, this) );
            ui->ltCorrectors->addWidget( new CaenPowerSupplyWidget(QString("TL1-PS-CR%1-Y").arg(i), false, this) );
        }
        ui->ltTriplets->addWidget( new CaenPowerSupplyWidget(QString("TL1-PS-TRP%1").arg(i), false, this) );
    }

    QObject::connect(ui->btnClose, SIGNAL(clicked()), this, SLOT(close()));
}

TL1CorrectorsWindow::~TL1CorrectorsWindow()
{
    delete ui;
}
