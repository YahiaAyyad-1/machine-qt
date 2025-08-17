#ifndef SR_COOLING_WINDOW_H
#define SR_COOLING_WINDOW_H

#include <QMainWindow>

#include "widgets/sr_cooling_box_widget.h"
#include "storage-ring/cooling/FormCellsThermocouples.h"
#include "storage-ring/cooling/FormCoolingPressure.h"
#include "storage-ring/vacuum/heat_absorbers_window.h"
#include "client.h"
#include <qepicspv.h>

namespace Ui {
class RingCoolingWindow;
}

class RingCoolingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RingCoolingWindow(QWidget *parent = nullptr);
    ~RingCoolingWindow();

private slots:
    void on_btnReset_clicked();

    void on_btnThermoCouples_clicked();

    void on_btnHeatAbsorbers_clicked();

    void on_btnPressure_clicked();

private:
    Ui::RingCoolingWindow *ui;

    FormCellsThermocouples* thc;
    FormCoolingPressure* pressure;
    HeatAbsorbersWindow* heat;

    QEpicsPV* pvHAB;
};

#endif // SR_COOLING_WINDOW_H
