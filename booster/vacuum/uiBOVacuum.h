#ifndef UIBOOSTERVACUUM_H
#define UIBOOSTERVACUUM_H

#include <QMainWindow>

#include "uiBoosterVacuumGC.h"
#include "uiBoosterIPC.h"
#include "general/valves_window.h"

namespace Ui {
class uiBOVacuum;
}

class uiBOVacuum : public QMainWindow
{
    Q_OBJECT

public:
    explicit uiBOVacuum(QWidget *parent = 0);
    ~uiBOVacuum();

private slots:
    void on_btnChannel1OFF_clicked();

    void on_btnChannel1ON_clicked();

    void on_btnChannel2OFF_clicked();

    void on_btnChannel2ON_clicked();

    void on_pushButton_clicked();

    void on_btnOpenIPC_clicked();

    void on_btnValves_clicked();

private:
    Ui::uiBOVacuum *ui;
    uiBoosterVacuumGC* boosterGC;
    uiBoosterIPC* boosterIPC;
    ValvesWindow* valves;
};

#endif // UIBOOSTERVACUUM_H
