#ifndef UISR_RFTEMPRATURES_H
#define UISR_RFTEMPRATURES_H

#include <QMainWindow>
#include <QDebug>
#include <qepicspv.h>

namespace Ui {
class uiSR_RFTempratures;
}

class uiSR_RFTempratures : public QMainWindow
{
    Q_OBJECT

public:
    explicit uiSR_RFTempratures(int ssa, QWidget *parent = 0);
    ~uiSR_RFTempratures();

private slots:
    void onDissipatorsTemperaturesChanged();

    void onTemperaturesChanged();

private:
    Ui::uiSR_RFTempratures *ui;
    // QEpicsPV* pvTempAvg[10];   // Temp average
    QList<QEpicsPV*> pvTempAvg;
};

#endif // UISR_RFTEMPRATURES_H
