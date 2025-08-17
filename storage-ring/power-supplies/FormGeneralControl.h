#ifndef FORMGENERALCONTROL_H
#define FORMGENERALCONTROL_H

#include <QMainWindow>
#include <qepicspv.h>

#include <client.h>
#include "macros.h"
#include "FormGeneralTuning.h"
#include "FormGeneralWaveform.h"
#include "FormGeneralParameters.h"

#define COMMAND_OFF     0
#define COMMAND_STANDBY 1
#define COMMAND_ON      2
#define COMMAND_FAULT   3
#define COMMAND_RESET   4
#define COMMAND_OPEN    5
#define COMMAND_SEMI_A  6
#define COMMAND_AUTO    7
#define COMMAND_MANUAL  8
#define COMMAND_STOP    9
#define COMMAND_PAUSE   10
#define COMMAND_RESUME  11
#define COMMAND_TRIGGER 12

#define STATE_OFF       0
#define STATE_STANDBY   1
#define STATE_ON        2
#define STATE_OPEN      4

#define MODE_DC         0
#define MODE_WAVEFORM   1

#define SEQUENCE_SEMIAUTO   3
#define SEQUENCE_SEMIAUTO_A 4
#define SEQUENCE_AUTO       5
#define SEQUENCE_AUTO_A     6
#define SEQUENCE_MANUAL     7
#define SEQUENCE_MANUAL_A   8

namespace Ui {
class FormGeneralControl;
}

class FormGeneralControl : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormGeneralControl(QString magnet, QWidget *parent = 0);
    ~FormGeneralControl();

private slots:
    void on_btnOpenloop_clicked();

    void on_btnOFF_clicked();

    void on_btnStandby_clicked();

    void on_btnON_clicked();

    void on_btnReset_clicked();

    void on_btnSemiauto_clicked();

    void on_Auto_clicked();

    void on_Manual_clicked();

    void on_btnTrigger_clicked();

    void on_btnPause_clicked();

    void on_btnResume_clicked();

    void on_btnStop_clicked();

    void on_btnDC_clicked();

    void on_btnWaveform_clicked();

    void stateHandlersChanged();

    void modesChanged();

    void sequencersChanged();

    void on_btnTuning_clicked();

    void on_btnWaveforms_clicked();

    void on_btnFirmware_clicked();

    void on_btnInterlock_clicked();

private:
    Ui::FormGeneralControl *ui;
    void sendCommand(int command);
    void setMode(int mode);

    FormGeneralTuning* tuning;
    FormGeneralWaveform* waveforms;
    FormGeneralParameters* parameters;

    QString magnet;
    QList<QEpicsPV*> states;
    QList<QEpicsPV*> modes;
    QList<QEpicsPV*> sequences;
};

#endif // FORMGENERALCONTROL_H
