#ifndef RING_PS_WINDOW_H
#define RING_PS_WINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QProcess>
#include <QLineEdit>
#include <qepicspv.h>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>

#define PS_WAVEFORM_SIZE 32768

#include "widgets/ps_widget.h"
#include "storage-ring/power-supplies/FormPulsedElements.h"
#include "storage-ring/power-supplies/sr_correctors_window.h"
#include "storage-ring/power-supplies/FormGatewaysHealth.h"
#include "storage-ring/power-supplies/FormGeneralControl.h"

#include "macros.h"

#define MAGNETS_COUNT 69

namespace Ui {
class RingPowerSupplyWindow;
}

class RingPowerSupplyWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RingPowerSupplyWindow(QWidget *parent = nullptr);
    ~RingPowerSupplyWindow();

    void setPSCurrent(QLineEdit *txt, QELabel *lbl, QString currentSet);

private slots:
    void onAllStateChanged();

    void on_btnReset_clicked();

    void on_btnPulsed_clicked();

    void on_btnCorrectors_clicked();

    void on_btnCycle_clicked();

    void on_btnRamp_clicked();

    void on_btnHealth_clicked();

    void on_cbGeneralControl_currentIndexChanged(int index);

    void onMachineStateChanged(QVariant value);

    void onQFConnected();

    void onQDConnected();

    void onSFConnected();

    void onSDConnected();

    void on_btnSetQF_clicked();

    void on_btnSetQD_clicked();

    void on_btnSetSF_clicked();

    void on_btnSetSD_clicked();

    void on_btnWaveform_clicked();

    void on_btnDC_clicked();

    void on_btnStandby_clicked();

    void on_btnON_clicked();

    void on_btnOpenloop_clicked();

    void on_btnOFF_clicked();

    void on_chkBoxIncludeRF_clicked(bool checked);

    void checkContentSize();

private:
    Ui::RingPowerSupplyWindow *ui;

    bool rampingWithRF;

    FormPulsedElements* pulsed;
    RingCorrectorsWindow* correctors;
    FormGatewaysHealth* health;
    FormGeneralControl* general;

    QTimer* timer;

    QEpicsPV* machineMode;
    QEpicsPV* qfCurrent;
    QEpicsPV* qdCurrent;
    QEpicsPV* sfCurrent;
    QEpicsPV* sdCurrent;
};

#endif // RING_PS_WINDOW_H
