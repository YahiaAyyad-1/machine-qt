#ifndef FORMDIAGNOSTICS_H
#define FORMDIAGNOSTICS_H

#include <QMainWindow>
#include <qepicspv.h>
#include <QMessageBox>

#include "FormFilling.h"
#include "FormBpmConfig.h"
#include "FormSRLiberaMain.h"
#include "FormBpmConfig.h"
#include "FormSRM.h"
#include "FormSRShaker.h"
#include "FormScraper.h"
#include "FormDCCT.h"
#include "FormBPMSchematic.h"
#include "FormFastInterlock.h"
#include "FormDCCTExpert.h"
#include "FormBLMChannels.h"
#include "pinhole_window.h"
#include "formbeatspicoammeter.h"
#include "FormInjectionEfficiency.h"
#include "vibration_analyzer_window.h"
#include "libera_spark_window.h"
#include "cameras_window.h"
#include "scopes_window.h"

#include "client.h"
#include "macros.h"


namespace Ui {
class FormDiagnostics;
}

class FormDiagnostics : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormDiagnostics(QWidget *parent = 0);
    ~FormDiagnostics();

private slots:
    void on_btnMoveOut_clicked();

    void beamEnergy_Changed();

    void motorData_Changed();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_btnSchematic_clicked();

    void on_btnFast_clicked();

    void on_btnConfig_clicked();

    void on_SRC10SetIn_clicked();

    void on_SRC06SetIn_clicked();

    void on_btnBLMPlots_clicked();

    void shutter_state();

    void SRC10SetIn();

    void SRC06SetIn();

    void on_qepushbutton_20_clicked();

    void on_btnGUI_clicked();

    void on_btnPinhole_clicked();

    void on_btnXbpm_clicked();

    void on_btnLibera_clicked();

    void on_btnEff_clicked();

    void on_btnVAN_clicked();

    void on_qepushbutton_9_clicked();

    void on_btnCameras_clicked();

    void on_btnScopesFCT_clicked();

private:
    Ui::FormDiagnostics *ui;

    FormFilling* filling;
    FormBpmConfig*  bpmConfig;
    FormSRLiberaMain*  libraMain;
    FormSRM* srm;
    FormSRShaker* shaker;
    FormScraper* scraper;
    FormDCCTExpert* dcct;
    FormBPMSchematic* bpm;
    FormFastInterlock* fast;
    FormBLMChannels* blm;
    PinholeWindow* pinhole;
    FormBeatsPicoammeter* beats_pico;
    FormInjectionEfficiency* eff;
    VibrationAnalyzerWindow* van;
    LiberaSparkWindow* spark;
    CamerasWindow* cams;
    ScopesWindow* fct;

    QEpicsPV* pvMotorRBV;
    QEpicsPV* pvMotorDIFF;
    QEpicsPV* pvMotorDMOV;
    QEpicsPV* pvEnergy;
    QEpicsPV* isIn_SRC10;
    QEpicsPV* isIn_SRC06;
    QEpicsPV* shutter_fault;
    QEpicsPV* shutter_closed;
    QEpicsPV* shutter_opened;
};

#endif // FORMDIAGNOSTICS_H
