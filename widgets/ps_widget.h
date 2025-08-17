#ifndef PS_WIDGET_H
#define PS_WIDGET_H

#include <QWidget>
#include <qepicspv.h>
#include <iostream>
#include "macros.h"

#include "storage-ring/power-supplies/uiSRPowerSupplyDetails.h"

#define STATE_OFF       0
#define STATE_STANDBY   1
#define STATE_ON        2
#define STATE_FAULT     3
#define STATE_OPENLOOP  4
#define STATE_TRANSIENT 5

#define SEQUENCE_IDLE               0
#define SEQUENCE_DC                 1
#define SEQUENCE_ARMED              2
#define SEQUENCE_SEMIAUTO           3
#define SEQUENCE_SEMIAUTO_ACTIVE    4
#define SEQUENCE_AUTO               5
#define SEQUENCE_AUTO_ACTIVE        6
#define SEQUENCE_MANUAL             7
#define SEQUENCE_MANUAL_ACTIVE      8

#define LABEL_DEFAULT_QSS \
    "QWidget { background-color: #e0dcda; color: #000000; }" \
    "QWidget { background-color: #e0eee0; }"

#define LABEL_ALARM_QSS \
    "QWidget { background-color: #e0dcda; color: #000000; }" \
    "QWidget { background-color: #e0eee0; }" \
    "QWidget { border:2px solid red; }"

namespace Ui {
class PowerSupplyWidget;
}

class PowerSupplyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PowerSupplyWidget(QString prefix, QWidget *parent = nullptr);
    ~PowerSupplyWidget();

    int psState;
    int psMode;
    QString prefix;

private slots:
    void onStateHandlerChanged(QVariant value);

    void onStateSequencerChanged(QVariant value);

    void on_btnDetails_clicked();

    void onModeChanged(QVariant value);

    void onMachineStateChanged(QVariant value);

    void onCurrentValueChanged(QVariant value);

private:
    Ui::PowerSupplyWidget *ui;

    uiSRPowerSupplyDetails* details;

    QEpicsPV* pvStateHandler;
    QEpicsPV* pvStateSequencer;
    QEpicsPV* pvMode;
    QEpicsPV* machineMode;
    QEpicsPV* pvGetCurrent;
    QEpicsPV* pvSetCurrent;
};

#endif // PS_WIDGET_H
