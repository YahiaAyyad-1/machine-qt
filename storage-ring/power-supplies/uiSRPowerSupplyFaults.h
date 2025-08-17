#ifndef UISRPOWERSUPPLYFAULTS_H
#define UISRPOWERSUPPLYFAULTS_H

#include <QMainWindow>

#include "FormFaultsExperts.h"
#include "macros.h"

namespace Ui {
class uiSRPowerSupplyFaults;
}

class uiSRPowerSupplyFaults : public QMainWindow
{
    Q_OBJECT

public:
    explicit uiSRPowerSupplyFaults(QString group, QWidget *parent = 0);
    ~uiSRPowerSupplyFaults();

private slots:
    void on_pushButton_clicked();

private:
    Ui::uiSRPowerSupplyFaults *ui;

    FormFaultsExperts* expert;

    QString group;
};

#endif // UISRPOWERSUPPLYFAULTS_H
