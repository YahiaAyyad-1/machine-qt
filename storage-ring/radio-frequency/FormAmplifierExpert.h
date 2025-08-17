#ifndef FORMAMPLIFIEREXPERT_H
#define FORMAMPLIFIEREXPERT_H

#include <QMainWindow>
#include <qwt_dial_needle.h>
#include <qwt_dial.h>
#include "qdebug.h"

#include "macros.h"
#include <qepicspv.h>
#include "client.h"

namespace Ui {
class FormAmplifierExpert;
}

class FormAmplifierExpert : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormAmplifierExpert(int ssa, QWidget *parent = 0);
    ~FormAmplifierExpert();

private slots:
    void preDriverPower_Changed();

    void on_btnReset_clicked();

    void on_btnSetPAVoltage_clicked();

    void on_btnSetAmpVoltage_clicked();

private:
    Ui::FormAmplifierExpert *ui;

    QEpicsPV* pvFWDPower;
    QEpicsPV* pvRFLPower;

    QString group;
    QString ssa_str;

    int ssa;
};

#endif // FORMAMPLIFIEREXPERT_H
