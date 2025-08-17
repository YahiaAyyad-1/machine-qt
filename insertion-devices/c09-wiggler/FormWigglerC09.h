#ifndef FORMWIGGLERC09_H
#define FORMWIGGLERC09_H

#include <QMainWindow>
#include <QDesktopWidget>

#include "galil/FormGalilController.h"
//#include "FormID09FastPS.h"
//#include "FormID09EasyPS.h"
#include "devices/caen-ps/caen_easy_ps_window.h"
#include "devices/caen-ps/caen_fast_ps_window.h"

#include "macros.h"
#include "client.h"

#include "qepicspv.h"

namespace Ui {
class FormWigglerC09;
}

class FormWigglerC09 : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormWigglerC09(QWidget *parent = 0);
    ~FormWigglerC09();

private slots:
    void on_btnMotion_clicked();

    void on_btnON_clicked();

    void on_btnOFF_clicked();

    void on_btnDetails1_clicked();

    void on_btnDetails2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_btnStop_clicked();

    void onLimitsChanged();

//    void on_btnMov_clicked();

private:
    Ui::FormWigglerC09 *ui;

    FormGalilController* galil;
    CaenFastPSWindow* fastPS;
    CaenEasyPSWindow* easyPS;

    QEpicsPV* pvLimits[6];
    QEpicsPV* current;
    QEpicsPV* energy;
    QEpicsPV* getGap;
    QEpicsPV* setGap;
    QEpicsPV* machineStatus;
    QEpicsPV* id9Status;
};

#endif // FORMWIGGLERC09_H
