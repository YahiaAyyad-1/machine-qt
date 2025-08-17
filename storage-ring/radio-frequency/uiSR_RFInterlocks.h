#ifndef UISR_RFINTERLOCKS_H
#define UISR_RFINTERLOCKS_H

#include <QMainWindow>
#include <qepicspv.h>
#include "client.h"

namespace Ui {
class uiSR_RFInterlocks;
}

class uiSR_RFInterlocks : public QMainWindow
{
    Q_OBJECT

public:
    explicit uiSR_RFInterlocks(QWidget *parent = 0,QString ssa="");
    ~uiSR_RFInterlocks();

private slots:
    void on_btnClose_clicked();

    void on_btnReset_clicked();

private:
    Ui::uiSR_RFInterlocks *ui;
    QEpicsPV*       pvDriver;               //Driver Interlocks lEDs
    QEpicsPV*       pvDissipators[10];     //Dissipators Interlocks LEDs
    QEpicsPV*       pvRF;                   //RF OFF LED
    QEpicsPV*       pvMains;               //Mains LED
    QString         ssa;             //Global varible
};

#endif // UISR_RFINTERLOCKS_H
