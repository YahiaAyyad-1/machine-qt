#ifndef UITL2DIAGNOSTICS_H
#define UITL2DIAGNOSTICS_H

#include <QMainWindow>
#include "client.h"
#include <QThread>

namespace Ui {
class uiTL2Diagnostics;
}

class uiTL2Diagnostics : public QMainWindow
{
    Q_OBJECT

public:
    explicit uiTL2Diagnostics(QWidget *parent = 0);
    ~uiTL2Diagnostics();

private slots:
    void on_btnClose_clicked();

//    void on_btnMoveCAM1In_clicked();

//    void on_btnMoveCAM2In_clicked();

//    void on_btnMoveCAM3In_clicked();

//    void on_btnMoveCAM4In_clicked();

//    void on_btnMoveCAM1Out_clicked();

//    void on_btnMoveCAM2Out_clicked();

//    void on_btnMoveCAM3Out_clicked();

//    void on_btnMoveCAM4Out_clicked();

    void on_btnScreensOut_clicked();

private:
    Ui::uiTL2Diagnostics *ui;
};

#endif // UITL2DIAGNOSTICS_H
