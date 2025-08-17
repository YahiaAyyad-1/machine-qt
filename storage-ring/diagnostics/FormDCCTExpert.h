#ifndef FORMDCCTEXPERT_H
#define FORMDCCTEXPERT_H

#include <QMainWindow>

#include <qepicspv.h>
#include "macros.h"
#include "client.h"

#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>

using namespace QT_CHARTS_NAMESPACE;

#define BUFFER_SIZE 60

namespace Ui {
class FormDCCTExpert;
}

class FormDCCTExpert : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormDCCTExpert(QString group, QWidget *parent = 0);
    ~FormDCCTExpert();

private slots:
    void on_cbSource_currentIndexChanged(int index);
    void onUpdateDcctPlot();

private:
    Ui::FormDCCTExpert *ui;
    QString group;

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

#endif // FORMDCCTEXPERT_H
