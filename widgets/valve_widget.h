#ifndef VALVE_WIDGET_H
#define VALVE_WIDGET_H

#include <QWidget>
#include <qepicspv.h>

namespace Ui {
class ValveWidget;
}

class ValveWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ValveWidget(QString prefix, bool isPSSValve = false, QWidget *parent = nullptr);
    ~ValveWidget();

    QString getPrefix();

private slots:
        void onMachineStatusValueChanged(const QVariant&);

private:
    Ui::ValveWidget *ui;

    QEpicsPV* machineStatus;
    QString prefix;
};

#endif // VALVE_WIDGET_H
