#ifndef GAUGES_SETPOINTS_WINDOW_H
#define GAUGES_SETPOINTS_WINDOW_H

#include <QMainWindow>

#include "widgets/gauge_setpoint_widget.h"
#include "macros.h"

namespace Ui {
class GaugesSetpointsWindow;
}

class GaugesSetpointsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GaugesSetpointsWindow(QWidget *parent = nullptr);
    ~GaugesSetpointsWindow();

private:
    Ui::GaugesSetpointsWindow *ui;
};

#endif // GAUGES_SETPOINTS_WINDOW_H
