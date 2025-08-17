#ifndef UISR_RFRECTIFIERS_H
#define UISR_RFRECTIFIERS_H

#include <QMainWindow>
#include <qepicspv.h>
#include "client.h"

namespace Ui {
class uiSR_RFRectifiers;
}

class uiSR_RFRectifiers : public QMainWindow
{
    Q_OBJECT

public:
    explicit uiSR_RFRectifiers(QWidget *parent = 0,QString ssa="");
    ~uiSR_RFRectifiers();

private slots:
    void on_btnClose_clicked();
    void on_btnSetAmpVoltage_clicked();

private:
    Ui::uiSR_RFRectifiers *ui;
    QEpicsPV*       pvVoltage[6];    //voltage pv
    QEpicsPV*       pvPower[6];     //power pv
    QString         ssa_Global;     //global variable ssas
    QTimer*         timer;          //timer variable
};

#endif // UISR_RFRECTIFIERS_H
