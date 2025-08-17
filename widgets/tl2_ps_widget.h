#ifndef TL2_PS_WIDGET_H
#define TL2_PS_WIDGET_H

#include <QWidget>
#include <qepicspv.h>

#define LABEL_DEFAULT_QSS \
    "QWidget { background-color: #e0dcda; color: #000000; }" \
    "QWidget { background-color: #e0eee0; }"

#define LABEL_ALARM_QSS \
    "QWidget { background-color: #e0dcda; color: #000000; }" \
    "QWidget { background-color: #e0eee0; }" \
    "QWidget { border:2px solid red; }"

namespace Ui {
class TL2PowerSupplyWidget;
}

class TL2PowerSupplyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TL2PowerSupplyWidget(QString prefix, QString enableSuffix, QString rsdSuffix, QStringList coolingPVs = {}, QWidget *parent = nullptr);
    ~TL2PowerSupplyWidget();

    void onCoolingPVsChanged();

    void onCurrentChanged(QVariant value);

    void onVoltageChanged(QVariant value);

private:
    Ui::TL2PowerSupplyWidget *ui;

    QString prefix;

    QEpicsPV* temperaturePV;
    QEpicsPV* flowPV;
    QEpicsPV* pvCurrent;
    QEpicsPV* pvVoltage;
};

#endif // TL2_PS_WIDGET_H
