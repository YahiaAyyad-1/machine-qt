#ifndef UISRPOWERSUPPLYDETAILS_H
#define UISRPOWERSUPPLYDETAILS_H

#include <QMainWindow>
#include <QDesktopWidget>
#include <qepicspv.h>
#include <QMessageBox>

#include "uiSRPowerSupplyTuning.h"
#include "uiSRPowerSupplyPlotter.h"
#include "uiSRPowerSupplyFaults.h"
#include "uiSRPowerSupplyReadings.h"
#include "FormWaveformSettings.h"
#include "FormParameters.h"
#include "FormDipoleFaults.h"
#include "general/FormPassword.h"

#include "macros.h"

namespace Ui {
class uiSRPowerSupplyDetails;
}

class uiSRPowerSupplyDetails : public QMainWindow
{
    Q_OBJECT

public:
    explicit uiSRPowerSupplyDetails(QString magnet, QWidget *parent = 0);
    ~uiSRPowerSupplyDetails();

private slots:
    void stateHandler_changed(QVariant value);
    void stateSequencer_changed(QVariant value);

    void on_pushButton_4_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_btnWaveforms_clicked();

    void on_btnFirmwareSettings_clicked();

    void onDipoleCurrentChanged(QVariant value);

    void showFirmwareSettingsParameters();

    void onMachineStatusChanged(QVariant value);

private:
    Ui::uiSRPowerSupplyDetails *ui;
    QString group;

    uiSRPowerSupplyTuning*   tuning;
    uiSRPowerSupplyPlotter*  plotter;
    uiSRPowerSupplyFaults*   uiFaults;
    uiSRPowerSupplyReadings* uiReadings;
    FormWaveformSettings*    waveforms;
    FormParameters*          parameters;
    FormDipoleFaults*        dipoleFaults;

    QEpicsPV* pvState;
    QEpicsPV* pvSequence;
    QEpicsPV* pvIload;
    QEpicsPV* pvStatus;
    QEpicsPV* machineMode;

    typedef enum
    {
        STATE_OFF = 0,
        STATE_STANDBY,
        STATE_ON,
        STATE_FAULT,
        STATE_OPENLOOP,
        STATE_TRANSIENT
    } PS_STATE;

    typedef enum
    {
        SEQUENCE_IDLE = 0,
        SEQUENCE_DC,
        SEQUENCE_ARMED,
        SEQUENCE_SEMIAUTO,
        SEQUENCE_SEMIAUTO_ACTIVE,
        SEQUENCE_AUTO,
        SEQUENCE_AUTO_ACTIVE,
        SEQUENCE_MANUAL,
        SEQUENCE_MANUAL_ACTIVE
    } PS_SEQUENCE;

};

#endif // UISRPOWERSUPPLYDETAILS_H
