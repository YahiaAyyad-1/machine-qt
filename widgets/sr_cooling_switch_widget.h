#ifndef SR_COOLING_SWITCH_WIDGET_H
#define SR_COOLING_SWITCH_WIDGET_H

#include <QWidget>

namespace Ui {
class RingCoolingSwitchWidget;
}

class RingCoolingSwitchWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RingCoolingSwitchWidget(int cell, QString device, QWidget *parent = nullptr);
    ~RingCoolingSwitchWidget();

private:
    Ui::RingCoolingSwitchWidget *ui;

    QString prefix;
};

#endif // SR_COOLING_SWITCH_WIDGET_H
