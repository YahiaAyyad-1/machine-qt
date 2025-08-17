#include "ion_pumps_window.h"
#include "ui_ion_pumps_window.h"

IonPumpsWindow::IonPumpsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IonPumpsWindow)
{
    ui->setupUi(this);
    int pumps = 0;
    for(int cell = 1; cell <= 16; cell++) {
        if(cell == 3 || cell == 14)
            pumps = 8;
        else if(cell % 2 == 0)
            pumps = 6;
        else
            pumps = 7;

        for (int p = 1; p <= pumps ; p++) {
            if( (cell == 11 && p == 1) || (cell == 9 && p == 3) )
                continue;

            if(cell <= 4)
                ui->ltQ1->addWidget(new IonPumpWidget(QString::asprintf("SRC%02d-VA-IP%d", cell, p), this));
            else if(cell <= 8)
                ui->ltQ2->addWidget(new IonPumpWidget(QString::asprintf("SRC%02d-VA-IP%d", cell, p), this));
            else if(cell <= 12)
                ui->ltQ3->addWidget(new IonPumpWidget(QString::asprintf("SRC%02d-VA-IP%d", cell, p), this));
            else
                ui->ltQ4->addWidget(new IonPumpWidget(QString::asprintf("SRC%02d-VA-IP%d", cell, p), this));
        }
    }

    ui->ltTL2_1->addWidget( new IonPumpWidget("TL2-VA-IP" + QString::number(1)));
    ui->ltTL2_1->addWidget( new IonPumpWidget("TL2-VA-IP" + QString::number(2)));
    ui->ltTL2_2->addWidget( new IonPumpWidget("TL2-VA-IP" + QString::number(3)));
    ui->ltTL2_2->addWidget( new IonPumpWidget("TL2-VA-IP" + QString::number(4)));
    ui->ltTL2_3->addWidget( new IonPumpWidget("TL2-VA-IP" + QString::number(5)));
    ui->ltTL2_3->addWidget( new IonPumpWidget("TL2-VA-IP" + QString::number(6)));
    ui->ltTL2_4->addWidget( new IonPumpWidget("TL2-VA-IP" + QString::number(7)));
    ui->ltTL2_4->addWidget( new IonPumpWidget("TL2-VA-IP" + QString::number(8)));

    CONNECT_CLOSE_BUTTON;
}

IonPumpsWindow::~IonPumpsWindow()
{
    delete ui;
}
