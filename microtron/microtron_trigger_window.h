#ifndef MI_TRIGGER_WINDOW_H
#define MI_TRIGGER_WINDOW_H

#include <QMainWindow>
#include "qepicspv.h"

#include "general/FormPassword.h"
#include "client.h"

namespace Ui {
class MicrotronTriggerWindow;
}

class MicrotronTriggerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MicrotronTriggerWindow(QWidget *parent = nullptr);
    ~MicrotronTriggerWindow();

private slots:
    void on_btnEmergency_clicked();

    void on_trigger_state_label_dbValueChanged(QString state);

    void triggerModeChanged(QVariant);

    void on_btnClose_clicked();

    void on_btnMaintenanceMode_clicked();

    void enableMaintenanceMode();

    void machineStateChanged(QVariant);

    void checkDevicesToTrigger(QVariant);

    void on_btnTriggerOn_clicked();

    void onTriggerOnTimeout();

    void onAGPSStateChanged();

    void onGunModStateChanged();

    void onMagModStateChanged();

private:
    Ui::MicrotronTriggerWindow *ui;

    QEpicsPV* triggerMode;
    QEpicsPV* agpsChecked;
    QEpicsPV* magModChecked;
    QEpicsPV* gunModChecked;
    QEpicsPV* machineState;
    QEpicsPV* agpsAckOn;

    QEpicsPV* pvAGPSState;
    QEpicsPV* pvGunModState;
    QEpicsPV* pvMagModState;

    QTimer* triggerOnTimer;
};

#endif // MI_TRIGGER_WINDOW_H
