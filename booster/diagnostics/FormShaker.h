#ifndef FORMSHAKER_H
#define FORMSHAKER_H

#include <QMainWindow>
#include <qepicspv.h>

#include "FormShakerInterlocks.h"

namespace Ui {
class FormShaker;
}

class FormShaker : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormShaker(QWidget *parent = 0);
    ~FormShaker();

private slots:
    void interlockStatus_Changed();

    void on_btnDetails1_clicked();

    void on_btnDetails2_clicked();

private:
    Ui::FormShaker *ui;

    FormShakerInterlocks* ilk;

    QString interlockPVs[6] = {"BO-DI-SHK1-CH1:isAmplifierTemperatureInterlock", "BO-DI-SHK1-CH1:isCurrentInterlock", "BO-DI-SHK1-CH1:isRFPowerInterlock",
                               "BO-DI-SHK1-CH2:isAmplifierTemperatureInterlock", "BO-DI-SHK1-CH2:isCurrentInterlock", "BO-DI-SHK1-CH2:isRFPowerInterlock"};

    QEpicsPV* shakerInterlocks[6];
};

#endif // FORMSHAKER_H
