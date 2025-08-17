#ifndef SR_VACUUM_WINDOW_H
#define SR_VACUUM_WINDOW_H

#include <QMainWindow>
#include <QLabel>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>
#include <qwt_point_data.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_marker.h>
#include <qwt_scale_div.h>
#include <qwt_scale_engine.h>
#include <qwt_scale_draw.h>

#include "widgets/vacuum_cell_widget.h"
#include "general/FormGauges.h"
#include "storage-ring/vacuum/ion_pumps_window.h"
#include "storage-ring/vacuum/heat_absorbers_window.h"
#include "storage-ring/vacuum/gauges_setpoints_window.h"
#include "general/valves_window.h"
#include "general/FormPassword.h"
#include "macros.h"

namespace Ui {
class RingVacuumWindow;
}

class RingVacuumWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RingVacuumWindow(QWidget *parent = nullptr);
    ~RingVacuumWindow();

private slots:
    void on_pushButton_clicked();

    void on_btnIonPumps_clicked();

    void on_btnValves_clicked();

    void on_btnHeatAbsorbers_clicked();

    void on_btnSetpoints_clicked();

    void gaugesVacuumChanged();

    void pumpsVacuumChanged();

    void open_set_points();

private:
    Ui::RingVacuumWindow *ui;

    IonPumpsWindow* ionPumps;
    FormGauges* gauges;
    GaugesSetpointsWindow* imgSp;
    ValvesWindow* valves;
    HeatAbsorbersWindow* heatAbs;

    QwtPointArrayData* imgPlotData;
    QwtPointArrayData* ipPlotData;

    QwtPlotCurve* imgCurve;
    QwtPlotCurve* ipCurve;

    QList<QEpicsPV*> pvListIMG;
    QList<QEpicsPV*> pvListIP;
};

class QwtAxisTickDraw : public QwtScaleDraw
{
public:
    QwtAxisTickDraw(double factor = 1.0);

protected:
    QwtText label(double value) const;
};

class QwtAxisTickDraw2 : public QwtScaleDraw
{
public:
    QwtAxisTickDraw2(double factor = 1.0);

protected:
    QwtText label(double value) const;
};

#endif // SR_VACUUM_WINDOW_H
