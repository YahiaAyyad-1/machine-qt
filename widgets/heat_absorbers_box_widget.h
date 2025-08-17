#ifndef HEAT_ABSORBERS_BOX_WIDGET_H
#define HEAT_ABSORBERS_BOX_WIDGET_H

#include <QWidget>
#include <widgets/heat_absorber_widget.h>

namespace Ui {
class HeatAbsorbersBoxWidget;
}

class HeatAbsorbersBoxWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HeatAbsorbersBoxWidget(QString config, QWidget *parent = nullptr);
    ~HeatAbsorbersBoxWidget();

private:
    Ui::HeatAbsorbersBoxWidget *ui;
};

#endif // HEAT_ABSORBERS_BOX_WIDGET_H
