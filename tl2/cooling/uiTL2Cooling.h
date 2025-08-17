#ifndef UITL2COOLING_H
#define UITL2COOLING_H

#include <QMainWindow>
#include "client.h"

namespace Ui {
class uiTL2Cooling;
}

class uiTL2Cooling : public QMainWindow
{
    Q_OBJECT

public:
    explicit uiTL2Cooling(QWidget *parent = 0);
    ~uiTL2Cooling();

private slots:
    void on_btnClose_clicked();

    void on_btnReset_clicked();

private:
    Ui::uiTL2Cooling *ui;
};

#endif // UITL2COOLING_H
