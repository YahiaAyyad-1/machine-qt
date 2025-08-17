#ifndef UIRFMAIN_H
#define UIRFMAIN_H

#include <QMainWindow>

#include <qepicspv.h>

#include "uiBORFSetpoints.h"

#include "client.h"

namespace Ui {
class uiBORFMain;
}

class uiBORFMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit uiBORFMain(QWidget *parent = 0);
    ~uiBORFMain();

private slots:
    void on_btnOpenLLE_clicked();

    void on_btnCavity_clicked();

    void on_btnResetInterlocks_clicked();

    void on_btnLoadProfile_clicked();

private:
    Ui::uiBORFMain *ui;
    uiBORFSetpoints* rfSp;

    QEpicsPV* pvMainAC;
    QEpicsPV* pvStatusTX;
};

#endif // UIRFMAIN_H
