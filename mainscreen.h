#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QMainWindow>
#include <QStyle>
#include <QDesktopWidget>
#include <QVBoxLayout>
#include <QApplication>
#include <QMessageBox>
#include <QScreen>
#include <qepicspv.h>

#include "microtron/uiMicrotron.h"
#include "microtron/uiMicrotronAnalog.h"
#include "microtron/FormMotors.h"
#include "microtron/microtron_trigger_window.h"
#include "microtron/microtron_coils_window.h"

#include "global/uiTSEventGenerator.h"
#include "general/event_receiver_window.h"

#include "tl1/power-supply/tl1_correctors_window.h"
#include "tl1/vacuum/uiTL1Vacuum.h"

#include "booster/radio-frequency/uiBORFMain.h"
#include "booster/cooling/uiBOCooling.h"
#include "booster/vacuum/uiBOVacuum.h"
#include "booster/power-supply/FormBoosterPS.h"
#include "booster/diagnostics/FormBoosterDI.h"

#include "tl2/cooling/uiTL2Cooling.h"
#include "tl2/power-supply/uiTL2PowerSupply.h"
#include "tl2/diagnostics/uiTL2Diagnostics.h"
#include "tl2/vacuum/uiTL2Vacuum.h"

#include "storage-ring/radio-frequency/uiSR_RF.h"
#include "storage-ring/cooling/sr_cooling_window.h"
#include "storage-ring/diagnostics/FormDiagnostics.h"
#include "storage-ring/diagnostics/FormDCCT.h"
#include "storage-ring/power-supplies/sr_ps_window.h"
#include "storage-ring/vacuum/ion_pumps_window.h"
#include "storage-ring/vacuum/sr_vacuum_window.h"
#include "storage-ring/vacuum/heat_absorbers_window.h"

#include "macros.h"
#include "general/FormMPS.h"
#include "general/FormProfiles.h"
#include "general/FormBeamlines.h"
#include "general/FormMachineManager.h"
#include "general/FormRadiationMonitors.h"
#include "general/FormInjection.h"
#include "general/FormMessage.h"
#include "general/FormBeamlinesStatus.h"
#include "general/beamlines_shutters.h"

#include "insertion-devices/c09-wiggler/FormWigglerC09.h"
#include "insertion-devices/c11-undulator/FormUndulatorC11.h"
#include "insertion-devices/c10-wiggler/Form3pwiggler.h"

namespace Ui {
class MainScreen;
}

class MainScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainScreen(QWidget *parent = 0);
    ~MainScreen();

private slots:
    void on_btnMIOperation_clicked();

    void on_btnSRPS_clicked();

    void on_btnMicrotronAnalog_clicked();

    void on_btnMicrotronPS_clicked();

    void on_btnTL1Power_clicked();

    void on_btnTL1Vacuum_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_8_clicked();

    void on_btnTL2Cooling_clicked();

    void on_btnTL2PowerSupplies_clicked();

    void on_btnTL2Diagnostics_clicked();

    void on_btnTL2Vacuum_clicked();

    void on_btnEVG_clicked();

    void on_btnEVR1_clicked();

    void on_btnEVR2_clicked();

    void on_btnSRVacuum_clicked();

    void on_btnSRRF_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_btnSRCooling_clicked();

    void on_btnSRDiagnostics_clicked();

    void on_btnMicrotronMotors_clicked();

    void on_btnMPS_clicked();

    void on_btnDCCT_clicked();

    void on_btnProfiles_clicked();

    void on_btnManager_clicked();

    void on_btnD09W_clicked();

    void on_btnMonitors_clicked();

    void on_btnInjection_clicked();

    void on_btnBeamlines_clicked();

    void on_btnMessage_clicked();

    void on_btnD11U_clicked();

    void on_btnD10W_clicked();

    void on_comMachineStatus_activated(int index);

    void on_btnBeamlinesShutters_clicked();

    void srBmPsValueChanged();

    void on_btnShuttersSafety_clicked();

private:
    Ui::MainScreen *ui;
    uiMicrotron* microtron;
    // uiMicrotronCoils* microtronCoils;
    MicrotronCoilsWindow* microtronCoils;
    uiMicrotronAnalog* microtronAnalog;
    FormMotors* microtronMotors;

    // uiTL1PowerSupply* tl1Power;
    TL1CorrectorsWindow* tl1Power;
    uiTL1Vacuum* tl1Vacuum;

    uiBORFMain* rfMain;
    uiBOCooling* cooling;
    uiBOVacuum* boVacuum;
    FormBoosterPS* boPS;
    FormBoosterDI* boDI;

    uiTL2Cooling* tl2Cooling;
    uiTL2Diagnostics* tl2Diagnostics;
    uiTL2PowerSupply* tl2Power;
    uiTL2Vacuum* tl2Vacuum;

    RingPowerSupplyWindow* srPower;
    RingVacuumWindow* srVacuum;
    uiSR_RF* srRF;
    RingCoolingWindow* srCooling;
    FormDiagnostics* srDiag;
    FormDCCT* dcct;

    uiTSEventGenerator* evg;
    EventReceiverWindow* evr0;
    EventReceiverWindow* evr1;

    FormMPS* mps;
    FormProfiles* profiles;
    FormBeamlines* beamlines;
    FormBeamlinesInterlocks* blInterlocks;
    FormMachineManager* manager;
    FormRadiationMonitors* monitors;
    FormInjection* injection;
    FormMessage* message;
    FormBeamlinesStatus* beamlinesShutters;

    FormWigglerC09* c09wiggler;
    FormUndulatorC11* c11Undulator;
    Form3pwiggler* c10wiggler;

    beamlines_shutters *shuttersSafety;
    QEpicsPV* srBmPs;
    int srBmPs_status = 0;
};

#endif // MAINSCREEN_H
