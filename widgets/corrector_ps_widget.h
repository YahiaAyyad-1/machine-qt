#ifndef CORRECTOR_PS_WIDGET_H
#define CORRECTOR_PS_WIDGET_H

#include <QWidget>

#include "qepicspv.h"
#include "storage-ring/power-supplies/FormCorrectorDetails.h"

namespace Ui {
class CorrectorPowerSupplyWidget;
}

class CorrectorPowerSupplyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CorrectorPowerSupplyWidget(QString prefix, QWidget *parent = nullptr);
    ~CorrectorPowerSupplyWidget();

    QString getPrefix();

private slots:
    void onStateHandlerChanged(QVariant value);

    void onFaultsChanged(QVariant value);

    void on_btnDetails_clicked();

    void onCurrentValueChanged(QVariant value);

    void onMachineStateChanged(QVariant value);



private:
    Ui::CorrectorPowerSupplyWidget *ui;

    FormCorrectorDetails* details;

    QEpicsPV* pvState;
    QEpicsPV* pvFaults;
    QEpicsPV* machineMode;
    QEpicsPV* pvGetCurrent;
    QEpicsPV* pvSetCurrent;
    QString prefix;
};

#endif // CORRECTOR_PS_WIDGET_H
