#ifndef POWER_METER_WIDGET_H
#define POWER_METER_WIDGET_H

#include <QMainWindow>

namespace Ui {
class power_meter_widget;
}

class power_meter_widget : public QMainWindow
{
    Q_OBJECT

public:
    explicit power_meter_widget(QString devNum, QString title, QString type, QWidget *parent = nullptr);
    ~power_meter_widget();

private:
    Ui::power_meter_widget *ui;
};

#endif // POWER_METER_WIDGET_H
