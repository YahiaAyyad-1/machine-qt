#ifndef ION_PUMP_WIDGET_H
#define ION_PUMP_WIDGET_H

#include <QWidget>
#include "macros.h"
#include "qepicspv.h"

namespace Ui {
class IonPumpWidget;
}

class IonPumpWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IonPumpWidget(QString group, QWidget *parent = nullptr);
    ~IonPumpWidget();

private slots:
    void pumpEnabledChanged(QVariant value);

private:
    Ui::IonPumpWidget *ui;

    QEpicsPV* enabled;

    QString group;
};

#endif // ION_PUMP_WIDGET_H
