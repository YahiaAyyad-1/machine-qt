#ifndef UISRPOWERSUPPLYTUNING_H
#define UISRPOWERSUPPLYTUNING_H

#include <QMainWindow>

#include "macros.h"

namespace Ui {
class uiSRPowerSupplyTuning;
}

class uiSRPowerSupplyTuning : public QMainWindow
{
    Q_OBJECT

public:
    explicit uiSRPowerSupplyTuning(QString group, QWidget *parent = 0);
    ~uiSRPowerSupplyTuning();

private:
    Ui::uiSRPowerSupplyTuning *ui;

    QString group;
};

#endif // UISRPOWERSUPPLYTUNING_H
