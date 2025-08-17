#ifndef FormSRLiberaMain_H
#define FormSRLiberaMain_H

#include <QMainWindow>
#include <qepicspv.h>
#include "client.h"
#include "macros.h"
#include <QThread>
#include "FormBPMHealth.h"
#include "FormGDX.h"

namespace Ui {
class FormSRLiberaMain;
}

class FormSRLiberaMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormSRLiberaMain(QWidget *parent = 0);
    ~FormSRLiberaMain();

private slots:
    void on_btnSync_clicked();

    void ledSyncStatus_Changed();

    void on_btnHealth_clicked();

    void on_btnGDX_clicked();

    void onLiberaHealthChanged();

    void on_btnEnablePm_clicked();

private:
    Ui::FormSRLiberaMain *ui;

    FormBPMHealth* health;
    FormGDX* gdx;

    QEpicsPV* pvLedSync[48];    //Led Sync All variables
    QList<QEpicsPV*> pvBPMTemps;
    QList<QEpicsPV*> pvBPMFans;
};

#endif // FormSRLiberaMain_H
