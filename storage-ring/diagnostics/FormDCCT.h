#ifndef FORMDCCT_H
#define FORMDCCT_H

#include <QMainWindow>
#include <qepicspv.h>
#include "macros.h"

#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>

using namespace QT_CHARTS_NAMESPACE;

#define BUFFER_SIZE 60

namespace Ui {
class FormDCCT;
}

class FormDCCT : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormDCCT(QWidget *parent = 0);
    ~FormDCCT();

private slots:
    void onUpdateDcctPlot();

private:
    Ui::FormDCCT *ui;

    QEpicsPV* pvDcct;
    QChart* chart;
    QSplineSeries* series;
    QTimer* timer;
    int numPoints;

    QVector<double> dcctCurrentValues;
    double min;
    double max;
    double margin;
};

#endif // FORMDCCT_H
