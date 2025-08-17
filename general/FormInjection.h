#ifndef FORMINJECTION_H
#define FORMINJECTION_H

#include <QMainWindow>
#include <QTimer>
#include <QHostInfo>
#include <cmath>

#include "qepicspv.h"

#include "booster/radio-frequency/uiBORFMain.h"
#include "FormBeamlines.h"
#include "FormMPS.h"
#include "storage-ring/diagnostics/FormDCCT.h"
#include "FormRadiationMonitors.h"
#include "storage-ring/radio-frequency/uiSR_RF.h"
#include "insertion-devices/c09-wiggler/FormWigglerC09.h"
#include "storage-ring/power-supplies/sr_correctors_window.h"
#include "storage-ring/vacuum/sr_vacuum_window.h"
#include "general/valves_window.h"
#include "storage-ring/cooling/sr_cooling_window.h"
#include "booster/vacuum/uiBOVacuum.h"
#include "booster/cooling/uiBOCooling.h"
#include "storage-ring/vacuum/uiSRGaugeInterlocks.h"
#include "general/FormProfiles.h"
#include "storage-ring/diagnostics/FormDiagnostics.h"
#include "microtron/uiMicrotron.h"
#include "microtron/FormMotors.h"
#include "general/FormMessage.h"
#include "storage-ring/power-supplies/uiSRPowerSupplyDetails.h"
#include "general/FormGauges.h"
#include "storage-ring/vacuum/ion_pumps_window.h"
#include "tl1/vacuum/uiTL1Vacuum.h"
#include "general/FormMainPower.h"
#include "booster/power-supply/FormBoosterPS.h"
#include "booster/diagnostics/FormBoosterDI.h"
#include "tl2/vacuum/uiTL2Vacuum.h"
#include "tl2/power-supply/uiTL2PowerSupply.h"
#include "tl2/diagnostics/uiTL2Diagnostics.h"
#include "tl2/cooling/uiTL2Cooling.h"
#include "microtron/microtron_trigger_window.h"
#include "microtron/microtron_coils_window.h"
#include "tl1/power-supply/tl1_correctors_window.h"
#include "storage-ring/power-supplies/sr_ps_window.h"
#include "microtron/uiMicrotronAnalog.h"
#include "general/FormPassword.h"
#include "FormCurrentLimit.h"
#include "FormSeptumInterlocks.h"
#include "FormBeamlinesInterlocks.h"
#include "storage-ring/diagnostics/FormInjectionEfficiency.h"
#include "general/FormFeedforwardStatus.h"
#include "general/FormControlExpert.h"
#include "storage-ring/diagnostics/FormBpmConfig.h"
#include "general/FormBeamlinesStatus.h"
#include "general/FormRadiationMonitors.h"

#include "client.h"
#include "macros.h"

#define PLOT_BUFFER 120


#define LABEL_DEFAULT_QSS \
    "QWidget { background-color: #e0dcda; color: #000000; }" \
    "QWidget { background-color: #e0eee0; }"

namespace Ui {
class FormInjection;
}

class FormInjection : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormInjection(QWidget *parent = 0);
    ~FormInjection();

private slots:
    void on_btnTimingOFF_clicked();

    void on_btnTimingON_clicked();

    void on_btnBORF_clicked();

    void on_btnBeamlines_clicked();

    void on_btnMPS_clicked();

    void on_btnDCCT_clicked();

    void on_btnMonitors_clicked();

    void on_btnSRRF_clicked();

    void allPVsChanged();

    void on_btnD09W_clicked();

    void on_btnSRPS_clicked();

    void on_btnCorrectors_clicked();

    void on_btnSRVacuum_clicked();

    void on_btnValves_clicked();

    void on_btnSRCooling_clicked();

    void on_btnBOVA_clicked();

    void on_btnBOCO_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_btnCycle_clicked();

    void on_btnRamp_clicked();

    void rfRampUpdate();

    void on_btnProfiles_clicked();

    void on_btnSRDiagnostics_clicked();

    void onComboBoxesChanged(int index);

    void on_btnMIOperation_clicked();

    void on_btnMicrotronMotors_clicked();

    void on_btnMicrotronPS_clicked();

    void onTargetChanged();

    void pvTimerTimeout();

    void on_pushButton_3_clicked();

    void on_btnMessage_clicked();

    void on_btnDetailsBM_clicked();

    void on_btnSeptumON_clicked();

    void on_btnSeptumOFF_clicked();

    void on_btnGauges_clicked();

    void on_btnTL1Vacuum_clicked();

    void on_btnMainPower_clicked();

    void onAGPSStateChanged();

    void onValvesStatusChanged();

    void on_btnIonPumps_clicked();

    void on_btnBOPower_clicked();

    void on_btnBODiag_clicked();

    void on_btnTL2Vacuum_clicked();

    void on_btnTL1Power_clicked();

    void on_btnTL2PowerSupplies_clicked();

    void on_btnTL2Diagnostics_clicked();

    void on_btnTL2Cooling_clicked();

    void on_btnSequencer_clicked();

    void onMachineStatusChanged(QVariant value);

    void on_btnBORF_2_clicked();

    void onKickValChanged();

    void on_btnMicrotronTemps_clicked();

    void on_comMachineStatus_activated(int index);

    void onCAVMaintenanceChanged();

    void on_btnCurrentLimit_clicked();

    void open_current_limit();

    void on_btnSeptumInterlocks_clicked();

    void onSeptumInterlock();

    void on_btnBeamlinesInterlocks_clicked();

    void on_btnEff_clicked();

    void on_btnFFStatus_clicked();

    void on_btnControlExpert_clicked();

    void open_control_expert();

    void on_btnSRDiagnostics_2_clicked();

    void on_btnBeamlinesShutters_clicked();


//    void txtIRStatus();

//    void txtXAFSStatus();

//    void txtMSStatus();

//    void txtBeatsStatus();

//    void txtHesebStatus();

//    void txtMSGap();

//    void txtBeatsGap();

//    void txtHesebGap();



    void onTuneXChanged();

    void onTuneYChanged();

    void on_chkBoxIncludeRf_clicked(bool checked);

    void on_btnRadiationMonitors_clicked();

    void on_btnRampDown_clicked();

private:
    Ui::FormInjection *ui;

    QMap<QString, QList<QEpicsPV*>> pvListsMap;

    QEpicsPV* pvBM;
    QList<QEpicsPV*> pvListQF;
    QList<QEpicsPV*> pvListQD;
    QList<QEpicsPV*> pvListSX;
    QList<QEpicsPV*> pvListHC;
    QList<QEpicsPV*> pvListVC;
    QList<QEpicsPV*> pvListSQ;
    QList<QEpicsPV*> pvListSRFS;
    QList<QEpicsPV*> pvListSRTS;
    QList<QEpicsPV*> pvListRFCO;
    QList<QEpicsPV*> pvListMDB;
    QList<QEpicsPV*> pvListBPM;
    QList<QEpicsPV*> pvListIMG;
    QList<QEpicsPV*> pvListBoosterVA;
    QList<QEpicsPV*> pvListBoosterPS;
    QList<QEpicsPV*> pvListBoosterCO;
    QList<QEpicsPV*> pvTL2Corr;
    QList<QEpicsPV*> pvTL2Quads;
    QList<QEpicsPV*> pvTL2THS;
    QList<QEpicsPV*> pvTL2BMX;
    QList<QEpicsPV*> pvSSAInterlocks;
    QList<QEpicsPV*> pvListBPMILK;
    QList<QEpicsPV*> pvTL2Vacuum;
    QList<QEpicsPV*> valve1FaultPVs;
    QList<QEpicsPV*> valve1ClosePVs;
    QList<QEpicsPV*> valve1OpenPVs;
    QList<QEpicsPV*> valve2FaultPVs;
    QList<QEpicsPV*> valve2ClosePVs;
    QList<QEpicsPV*> valve2OpenPVs;
    QEpicsPV* pvCurrent;
    QEpicsPV* pvEnergy;
    QEpicsPV* pvOP;
    QEpicsPV* pvCurrentBO;
    QEpicsPV* pvCTR;
    QEpicsPV* pvAGPS;
    QEpicsPV* pvStatus;
    QEpicsPV* pvListBL;
    QEpicsPV* pvKick;
    QEpicsPV* pvCAVMaintenance1;
    QEpicsPV* pvCAVMaintenance2;
    QEpicsPV* pvCAVMaintenance3;
    QEpicsPV* pvCAVMaintenance4;
    QEpicsPV* pvSeptumCurrentLimit;
    QEpicsPV* pvSeptumMs;
    QEpicsPV* pvSeptumHeseb;
    QEpicsPV* pvSeptumBeats;
    QEpicsPV* pvTuneX;
    QEpicsPV* pvTuneY;
    QEpicsPV* pvIRStatus;
    QEpicsPV* pvXAFSStatus;
    QEpicsPV* pvMSStatus;
    QEpicsPV* pvBeatsStatus;
    QEpicsPV* pvHesebStatus;
    QEpicsPV* pvMSGap;
    QEpicsPV* pvBeatsGap;
    QEpicsPV* pvHesebGap;
    QEpicsPV* pvHesebShift;

    QTimer* rfRampTimer;
    QTimer* pvTimer;
    QList<int> psc_warnings;
    bool rampingWithRF;

    uiBORFMain* boRF;
    FormBeamlines* beamlines;
    FormMPS* mps;
    FormDCCT* dcct;
    FormRadiationMonitors* monitors;
    uiSR_RF* rf;
    FormWigglerC09* wiggler09;
    RingPowerSupplyWindow* srPS;
    RingCorrectorsWindow* crPS;
    RingVacuumWindow* srVacuum;
    ValvesWindow* valves;
    RingCoolingWindow* cooling;
    uiBOVacuum* boVac;
    uiBOCooling* boCool;
    uiSRGaugeInterlocks* img;
    FormProfiles* profiles;
    FormDiagnostics* srDI;
    uiMicrotron* mi;
    FormMotors* motors;
    MicrotronCoilsWindow* coils;
    FormMessage* message;
    uiSRPowerSupplyDetails* bmDetails;
    FormGauges* gauges;
    IonPumpsWindow* ionPumps;
    uiTL1Vacuum* tl1Vacuum;
    FormMainPower* mainPower;
    FormBoosterPS* boosterPS;
    FormBoosterDI* boosterDI;
    uiTL2Vacuum* tl2Vacuum;
    TL1CorrectorsWindow* tl1Power;
    uiTL2PowerSupply* tl2Power;
    uiTL2Diagnostics* tl2Diag;
    uiTL2Cooling* tl2Cooling;
    MicrotronTriggerWindow* sequencer;
    uiMicrotronAnalog* microtronAnalog;
    FormInjectionEfficiency* eff;
    FormFeedforwardStatus* ffStatus;
    FormBpmConfig* bpmConfig;
    FormBeamlinesStatus* beamlinesShutters;
    FormRadiationMonitors* radiationMonitors;
};

#endif // FORMINJECTION_H
