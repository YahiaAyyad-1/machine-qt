#ifndef UISR_RFCOOLINGRACKS_H
#define UISR_RFCOOLINGRACKS_H

#include <QMainWindow>
#include "qepicspv.h"

namespace Ui {
class uiSR_RFCoolingRacks;
}

class uiSR_RFCoolingRacks : public QMainWindow
{
    Q_OBJECT

public:
    explicit uiSR_RFCoolingRacks(QWidget *parent = 0);
    ~uiSR_RFCoolingRacks();

private slots:
    void on_btnClose_clicked();
    void onMachineStateChanged(QVariant value);

private:
    Ui::uiSR_RFCoolingRacks *ui;
    QEpicsPV* machineMode;

};

#endif // UISR_RFCOOLINGRACKS_H
