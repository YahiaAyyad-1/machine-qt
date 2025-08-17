#ifndef UISRPOWERSUPPLYPLOTTER_H
#define UISRPOWERSUPPLYPLOTTER_H

#include <QMainWindow>

#include <math.h>

namespace Ui {
class uiSRPowerSupplyPlotter;
}

class uiSRPowerSupplyPlotter : public QMainWindow
{
    Q_OBJECT

public:
    explicit uiSRPowerSupplyPlotter(QString group, QWidget *parent = 0);
    ~uiSRPowerSupplyPlotter();

private slots:
    void on_pltILoad_mouseMove(const QPointF &posn);

    void on_pltILoad_dbValueChanged(double out);

private:
    Ui::uiSRPowerSupplyPlotter *ui;

    QList<double> plotData;
};

#endif // UISRPOWERSUPPLYPLOTTER_H
