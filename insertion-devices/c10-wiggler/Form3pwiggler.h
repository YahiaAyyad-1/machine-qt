#ifndef FORM3PWIGGLER_H
#define FORM3PWIGGLER_H

#include <QMainWindow>
#include <qepicspv.h>
#include "client.h"
#include "macros.h"
#include "devices/caen-ps/caen_easy_ps_window.h"
#include "devices/caen-ps/caen_fast_ps_window.h"
#include "galil/FormGalilController.h"
#include <QThread>
namespace Ui {
class Form3pwiggler;
}

class Form3pwiggler : public QMainWindow
{
    Q_OBJECT

public:
    explicit Form3pwiggler(QWidget *parent = nullptr);
    ~Form3pwiggler();

private slots:
    void on_btnStop_clicked();

    void on_btnDetailsY1_clicked();

    void on_btnDetailsY2_clicked();

    void on_btnMotion_clicked();

    void on_btnDetailsX1_clicked();

    void on_btnDetailsX2_clicked();

    void motorsEnableLed();

    void emergency1();
    void emergency2();

    void on_btnAlarmsReset_clicked();

    void on_btnSwitchesReset_clicked();

//    void on_btnMov_clicked();

private:
    Ui::Form3pwiggler *ui;
    CaenEasyPSWindow* easyPS;
    FormGalilController* galil;
    CaenFastPSWindow* fastPS;

    QEpicsPV* pvEmergency1;
    QEpicsPV* pvEmergency2;
    QEpicsPV* pvEmergency3;
    QEpicsPV* pvEmergency4;
    QEpicsPV* pvMotor1Enable;
    QEpicsPV* pvMotor2Enable;
    QEpicsPV* current;
    QEpicsPV* energy;
    QEpicsPV* getGap;
    QEpicsPV* setGap;
    QEpicsPV* machineStatus;
    QEpicsPV* id10Status;
};

#endif // FORM3PWIGGLER_H
