#ifndef FORMBOOSTERPS_H
#define FORMBOOSTERPS_H

#include <QMainWindow>
#include <QDesktopWidget>

#include <qepicspv.h>

#include "FormBoosterCorrectors.h"
#include "FormBoosterPulsed.h"
#include "FormBoosterDCPower.h"
#include "FormBMInterlocks.h"
#include "FormDCInterlocks.h"

#include "macros.h"

#define TRIGGER_OFF         0
#define TRIGGER_CONTINUOUS  1073741822

namespace Ui {
class FormBoosterPS;
}

class FormBoosterPS : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormBoosterPS(QWidget *parent = 0);
    ~FormBoosterPS();

private slots:
    void on_btnOpenCorrectors_clicked();

    void on_btnOpenPulsed_clicked();

    void on_btnDisableTiming_clicked();

    void on_btnEnableTiming_clicked();

    void timingEnabled_Changed();

    void on_btnOpenDC_clicked();

    void on_btnStandby_clicked();

    void on_btnPowerOn_clicked();

    void on_btnPulseOn_clicked();

    void on_cbTrigger_currentIndexChanged(int index);

    void on_btnBMLocks_clicked();

    void on_btnQFLocks_clicked();

    void on_btnQDLocks_clicked();

    void interlocksChanged();

    void statesChanged();

    void onCorrectorsChanged();

    void on_btnOFF_clicked();

    void on_btnCont_clicked();

private:
    Ui::FormBoosterPS *ui;

    FormBoosterCorrectors* correctors;
    FormBoosterPulsed* pulsed;
    FormBoosterDCPower* dc;
    FormBMInterlocks* bmInterlocks;
    FormDCInterlocks* dcInterlocks;

    QEpicsPV* pvTiming1;
    QEpicsPV* pvTiming2;
    QEpicsPV* pvTiming3;
    QEpicsPV* pvBMInterlocks[7];
    QEpicsPV* pvQFInterlocks[6];
    QEpicsPV* pvQDInterlocks[6];
    QEpicsPV* pvState[3];
    QEpicsPV* pvCR[6];
};

#endif // FORMBOOSTERPS_H
