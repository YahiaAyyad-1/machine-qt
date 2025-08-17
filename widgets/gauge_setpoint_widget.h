#ifndef GAUGE_SETPOINT_WIDGET_H
#define GAUGE_SETPOINT_WIDGET_H

#include <QWidget>

namespace Ui {
class GaugeSetpointWidget;
}

class GaugeSetpointWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GaugeSetpointWidget(QString imgPrefix, int gc, int channel, bool isRedundant = true, QWidget *parent = nullptr);
    ~GaugeSetpointWidget();

private:
    Ui::GaugeSetpointWidget *ui;
};

#endif // GAUGE_SETPOINT_WIDGET_H
