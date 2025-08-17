#ifndef HEAT_ABSORBER_WIDGET_H
#define HEAT_ABSORBER_WIDGET_H

#include <QWidget>

namespace Ui {
class HeatAbsorberWidget;
}

class HeatAbsorberWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HeatAbsorberWidget(QString pvName, QString text, QWidget *parent = nullptr);
    ~HeatAbsorberWidget();

private:
    Ui::HeatAbsorberWidget *ui;
};

#endif // HEAT_ABSORBER_WIDGET_H
