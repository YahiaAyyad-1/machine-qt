#ifndef FORMVACUUMSCHEMATIC_H
#define FORMVACUUMSCHEMATIC_H

#include <QMainWindow>
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

#include <qepicspv.h>

#include "macros.h"

namespace Ui {
class FormVacuumSchematic;
}

class FormVacuumSchematic : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormVacuumSchematic(QWidget *parent = 0);
    ~FormVacuumSchematic();

private slots:
    void imgVacuumChanged();

    void ipVacuumChanged();

private:
    Ui::FormVacuumSchematic *ui;

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

#endif // FORMVACUUMSCHEMATIC_H
