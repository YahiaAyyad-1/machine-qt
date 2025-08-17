#ifndef FORMBPMSCHEMATIC_H
#define FORMBPMSCHEMATIC_H

#include <QMainWindow>
#include <QMessageBox>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>
#include <qwt_point_data.h>
#include <qwt_plot_grid.h>
#include <qepicspv.h>

#include "macros.h"

namespace Ui {
class FormBPMSchematic;
}

class FormBPMSchematic : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormBPMSchematic(QWidget *parent = 0);
    ~FormBPMSchematic();

private slots:
    void verticalDataChanged();

    void horizontalDataChanged();

private:
    Ui::FormBPMSchematic *ui;

    QwtPointArrayData* xPlotData;
    QwtPointArrayData* yPlotData;

    QwtPlotCurve* xCurve;
    QwtPlotCurve* yCurve;

    QList<QEpicsPV*> xData;
    QList<QEpicsPV*> yData;
};

#endif // FORMBPMSCHEMATIC_H
