#ifndef FORMPULSEDELEMENTS_H
#define FORMPULSEDELEMENTS_H

#include <QMainWindow>
#include <qepicspv.h>

#include <macros.h>
#include "client.h"
#include "FormPID.h"
#include "general/FormSeptumInterlocks.h"

namespace Ui {
class FormPulsedElements;
}

class FormPulsedElements : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormPulsedElements(QWidget *parent = 0);
    ~FormPulsedElements();

private slots:
    void on_btnPID_clicked();

    void onModeChanged(QVariant value);

    void on_btnON_clicked();

    void on_btnOFF_clicked();

    void onKickerVoltageChanged(QVariant value);

    void on_btnSeptumInterlocks_clicked();

    void onSeptumInterlock();

    void onMachineStatusChanged(QVariant);

private:
    Ui::FormPulsedElements *ui;

    FormPID* pid;

    QEpicsPV* mode;
    QEpicsPV* voltage;
    QEpicsPV* machineStatus;
    QEpicsPV* pvSeptumCurrentLimit;
    QEpicsPV* pvSeptumMs;
    QEpicsPV* pvSeptumHeseb;
    QEpicsPV* pvSeptumBeats;
};

#endif // FORMPULSEDELEMENTS_H
