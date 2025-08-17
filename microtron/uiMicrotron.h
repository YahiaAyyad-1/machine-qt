#ifndef UIMICROTRON_H
#define UIMICROTRON_H

#include <QMainWindow>
#include <qepicspv.h>
// #include <QCaObject.h>
#include "microtron/microtron_trigger_window.h"
#include "general/FormPassword.h"
#include "macros.h"
#include "formsetcurrent.h"
#include "FormTimer.h"
#include "storage-ring/diagnostics/scopes_window.h"

namespace Ui {
class uiMicrotron;
}

// using namespace qcaobject;

class uiMicrotron : public QMainWindow
{
    Q_OBJECT

public:
    explicit uiMicrotron(QWidget *parent = 0);
    ~uiMicrotron();

private slots:
    void on_btnRampUp_clicked();

    void on_btnReset_clicked();

    void on_btnPowerOff_clicked();

    void on_btnClose_clicked();

    void on_btnPowerOn_clicked();

    void on_btnMagnetOff_clicked();

    void on_btnMagnetOn_clicked();

    void on_btnFilamentOff_clicked();

    void on_btnFilamentOn_clicked();

    void on_btnHighVoltageOff_clicked();

    void on_btnHighVoltageOn_clicked();

    void rampStatusChanged();

//    void filamentHoursChanged();

    void onAGPSStateChanged();

    void onAGPSWarningsChanged();

    void on_btnSequencer_clicked();

    void on_btnSetCurrent_clicked();
    void open_set_current();

    void on_btnCycle_clicked();

    void onGunStateChanged();

    void onMagStateChanged();

    void onGunInterlocksChanged();

    void onMagInterlocksChanged();

    void onGunTriggerStateChanged();

    void onMagTriggerStateChanged();


    void on_btnTimers_clicked();

    void on_btnScope_clicked();

private:
    Ui::uiMicrotron *ui;

    MicrotronTriggerWindow* trigger;
    ScopesWindow* scope;

    FormPassword* set_current_pass;
    QEpicsPV* pvShutdown;
    QEpicsPV* pvRamp;
    QEpicsPV* pvSequence;
    QEpicsPV* pvFilament;
    QEpicsPV* pvAGPSState;
    QEpicsPV* pvAGPSWarnings;
    QEpicsPV* pvGunState;
    QEpicsPV* pvMagState;
    QEpicsPV* pvGunTriggerInterlocks;
    QEpicsPV* pvMagTriggerInterlocks;
    QEpicsPV* pvGunStandbyInterlocks;
    QEpicsPV* pvMagStandbyInterlocks;
    QEpicsPV* pvGunHVInterlocks;
    QEpicsPV* pvMagHVInterlocks;
    QEpicsPV* pvGunTrigger;
    QEpicsPV* pvMagTrigger;
};

#endif // UIMICROTRON_H
