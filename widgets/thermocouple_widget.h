#ifndef THERMOCOUPLE_WIDGET_H
#define THERMOCOUPLE_WIDGET_H

#include <QWidget>

namespace Ui {
class ThermocoupleWidget;
}

class ThermocoupleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ThermocoupleWidget(QString name, QString prefix, QWidget *parent = nullptr);
    ~ThermocoupleWidget();

private:
    Ui::ThermocoupleWidget *ui;

    QString prefix;
};

#endif // THERMOCOUPLE_WIDGET_H
