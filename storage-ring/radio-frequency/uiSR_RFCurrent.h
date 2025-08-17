#ifndef UISR_RFCURRENT_H
#define UISR_RFCURRENT_H

#include <QMainWindow>
#include <qepicspv.h>

namespace Ui {
class uiSR_RFCurrent;
}

class uiSR_RFCurrent : public QMainWindow
{
    Q_OBJECT

public:
    explicit uiSR_RFCurrent(QWidget *parent = 0,QString ssa="");
    ~uiSR_RFCurrent();

private slots:
    void preDriverPower_Changed();

private:
    Ui::uiSR_RFCurrent *ui;
    QEpicsPV*       pvInputCurrent[10];     //check Input Current
    QEpicsPV*       pvOutputCurrent[10];    //check Output Current
    QEpicsPV*       pvPI1[10];              //PI1 pv
    QEpicsPV*       pvPR1[10];              //PR1 pv
    QEpicsPV*       pvPI2[10];              //PI2 pv
    QEpicsPV*       pvPR2[10];              //PR2 pv
    QEpicsPV*       pvFWDPower;             //check Forward Power
    QEpicsPV*       pvRFLPower;             //check Reflected Power
    QEpicsPV*       pvLblDriverPower[2];
};

#endif // UISR_RFCURRENT_H
