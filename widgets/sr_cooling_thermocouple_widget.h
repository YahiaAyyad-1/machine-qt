#ifndef SR_COOLING_THERMOCOUPLE_WIDGET_H
#define SR_COOLING_THERMOCOUPLE_WIDGET_H

#include <QWidget>
#include "qepicspv.h"

namespace Ui {
class sr_cooling_thermocouple_widget;
}

class sr_cooling_thermocouple_widget : public QWidget
{
    Q_OBJECT

public:
    explicit sr_cooling_thermocouple_widget(int cellNumber, QWidget *parent = nullptr);
    ~sr_cooling_thermocouple_widget();

private slots:
    void onEnablePvchange(const QVariant&);

private:
    Ui::sr_cooling_thermocouple_widget *ui;

    QEpicsPV* enablePv;
};

#endif // SR_COOLING_THERMOCOUPLE_WIDGET_H
