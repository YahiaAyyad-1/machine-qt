#ifndef SR_COOLING_BOX_WIDGET_H
#define SR_COOLING_BOX_WIDGET_H

#include <QWidget>

#include "sr_cooling_switch_widget.h"

namespace Ui {
class RingCoolingBoxWidget;
}

class RingCoolingBoxWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RingCoolingBoxWidget(int cell, QWidget *parent = nullptr);
    ~RingCoolingBoxWidget();

private:
    Ui::RingCoolingBoxWidget *ui;

    QString devices[9] = {"SF1", "QF1", "QD1", "SD1", "BM", "SD2", "QD2", "QF2", "SF2"};
};

#endif // SR_COOLING_BOX_WIDGET_H
