#ifndef UISRPOWERSUPPLYREADINGS_H
#define UISRPOWERSUPPLYREADINGS_H

#include <QMainWindow>

#include "macros.h"

namespace Ui {
class uiSRPowerSupplyReadings;
}

class uiSRPowerSupplyReadings : public QMainWindow
{
    Q_OBJECT

public:
    explicit uiSRPowerSupplyReadings(QString group, QWidget *parent = 0);
    ~uiSRPowerSupplyReadings();

private slots:
    void on_pushButton_clicked();

private:
    Ui::uiSRPowerSupplyReadings *ui;
    QString group;
};

#endif // UISRPOWERSUPPLYREADINGS_H
