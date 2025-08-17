#ifndef FORMBPMCONFIG_H
#define FORMBPMCONFIG_H

#include <QMainWindow>
#include <qepicspv.h>
#include "client.h"
#include "macros.h"

#include <QIntValidator>

namespace Ui {
class FormBpmConfig;
}

class FormBpmConfig : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormBpmConfig(QWidget *parent = 0);
    ~FormBpmConfig();
    void setParameter(QString parameter, int value);
    void setParameter(QString parameter, double value);

private slots:
    void on_btnInterlockEnable_clicked();

    void on_btnInterlockDisable_clicked();

    void on_btnGainEnable_clicked();

    void on_btnGainDisable_clicked();

    void on_btnSetAtt_clicked();

    void on_btnSetMinX_clicked();

    void on_btnSetMaxX_clicked();

    void on_btnSetMinY_clicked();

    void on_btnSetMaxY_clicked();

    void on_btnSetOVF_clicked();

    void on_btnSetOVFTime_clicked();

    void on_btnSetfilter_clicked();

    void on_btnSetLimit_clicked();

    void interlocksChanged();

    void gainEnabledChanged();

    void interlocksCountChanged();

    void on_btnReset_clicked();

    void positionLimitsChanged();

    void on_btnSet_clicked();

    void on_lblBPM0Min_dbValueChanged();

    void on_lblBPM0Max_dbValueChanged();

    void on_lblBPM1Min_dbValueChanged();

    void on_lblBPM1Max_dbValueChanged();

    void on_lblBPM2Min_dbValueChanged();

    void on_lblBPM2Max_dbValueChanged();

    void on_lblBPM3Min_dbValueChanged();

    void on_lblBPM3Max_dbValueChanged();

private:
    Ui::FormBpmConfig *ui;

    QList<QEpicsPV*> interlocksPVs;
    QList<QEpicsPV*> gainPVs;
    QList<QEpicsPV*> pvInterlocked;
    QList<QEpicsPV*> pvMinX;
    QList<QEpicsPV*> pvMinY;
    QList<QEpicsPV*> pvMaxX;
    QList<QEpicsPV*> pvMaxY;
    QEpicsPV* BPM0Min;
    QEpicsPV* BPM0Max;
    QEpicsPV* BPM1Min;
    QEpicsPV* BPM1Max;
    QEpicsPV* BPM2Min;
    QEpicsPV* BPM2Max;
    QEpicsPV* BPM3Min;
    QEpicsPV* BPM3Max;
};

#endif // FORMBPMCONFIG_H
