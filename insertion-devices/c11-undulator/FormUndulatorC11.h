#ifndef FORMUNDULATORC11_H
#define FORMUNDULATORC11_H

#include <QMainWindow>
// #include "insertion-devices/c11-undulator/FormID11EasyPS.h"
#include "devices/caen-ps/caen_easy_ps_window.h"

#include "macros.h"
#include "client.h"

#include "qepicspv.h"
namespace Ui {
class FormUndulatorC11;
}

class FormUndulatorC11 : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormUndulatorC11(QWidget *parent = nullptr);
    ~FormUndulatorC11();

private slots:
    void on_btnHC1Details_clicked();

    void on_btnVC1Details_clicked();

    void on_btnHC2Details_clicked();

    void on_btnVC2Details_clicked();

    void on_btnON_clicked();

    void on_btnOFF_clicked();

//    void on_btnStop_clicked();

//    void stop_btn_on_start();


private:
    Ui::FormUndulatorC11 *ui;

    CaenEasyPSWindow* easyPS;

    QEpicsPV* stopStatus;
};

#endif // FORMUNDULATORC11_H
