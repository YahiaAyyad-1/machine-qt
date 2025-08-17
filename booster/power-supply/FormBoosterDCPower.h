#ifndef FORMBOOSTERDCPOWER_H
#define FORMBOOSTERDCPOWER_H

#include <QMainWindow>
#include <QDebug>
#include <qepicspv.h>

#include "FormDCConfig.h"
#include "FormDCInterlocks.h"
#include "FormBMInterlocks.h"

#define PULSE_ON    8
#define POWER_ON    6
#define STANDBY     2
#define STOP_SEQ    10
#define INRUSH_SEQ  3

namespace Ui {
class FormBoosterDCPower;
}

class FormBoosterDCPower : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormBoosterDCPower(QWidget *parent = 0);
    ~FormBoosterDCPower();

private slots:
    void powerState_Changed();
    void powerInterlocks_Changed();

    void on_btnConfig_clicked();

    void on_btnBMPower_clicked();

    void on_btnQFPower_clicked();

    void on_btnQDPower_clicked();

    void on_btnQFInterlocks_clicked();

    void on_btnQDInterlocks_clicked();

    void on_btnBMInterlocks_clicked();

private:
    Ui::FormBoosterDCPower *ui;

    FormDCConfig* config;
    FormDCInterlocks* dcInterlocks;
    FormBMInterlocks* bmInterlocks;

    QEpicsPV* pvBMState;
    QEpicsPV* pvQFState;
    QEpicsPV* pvQDState;
    QEpicsPV* pvBMInterlocks1;
    QEpicsPV* pvBMInterlocks2;
    QEpicsPV* pvBMInterlocks3;
    QEpicsPV* pvBMInterlocks4;
    QEpicsPV* pvBMInterlocks5;
    QEpicsPV* pvBMInterlocks6;
    QEpicsPV* pvBMInterlocks7;
    QEpicsPV* pvQFInterlocks1;
    QEpicsPV* pvQFInterlocks2;
    QEpicsPV* pvQFInterlocks3;
    QEpicsPV* pvQDInterlocks1;
    QEpicsPV* pvQDInterlocks2;
    QEpicsPV* pvQDInterlocks3;
};

#endif // FORMBOOSTERDCPOWER_H
