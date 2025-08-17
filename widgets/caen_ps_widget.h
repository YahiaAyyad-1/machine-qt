#ifndef MICROTRON_COIL_WIDGET_H
#define MICROTRON_COIL_WIDGET_H

#include <QWidget>
#include "macros.h"
#include "devices/caen-ps/caen_easy_ps_window.h"
#include "devices/caen-ps/caen_fast_ps_window.h"

namespace Ui {
class CaenPowerSupplyWidget;
}

class CaenPowerSupplyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CaenPowerSupplyWidget(QString group, bool isFastPS = false, QWidget *parent = nullptr);
    ~CaenPowerSupplyWidget();

private slots:
    void on_btnDetails_clicked();

private:
    Ui::CaenPowerSupplyWidget *ui;
    CaenEasyPSWindow* psDetails;
    CaenFastPSWindow* fastPSDetails;

    QString group;
    bool isFastPS;
};

#endif // MICROTRON_COIL_WIDGET_H
