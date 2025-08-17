#ifndef UITL1VACUUM_H
#define UITL1VACUUM_H

#include <QMainWindow>

#include "general/valves_window.h"

namespace Ui {
class uiTL1Vacuum;
}

class uiTL1Vacuum : public QMainWindow
{
    Q_OBJECT

public:
    explicit uiTL1Vacuum(QWidget *parent = 0);
    ~uiTL1Vacuum();

private slots:
    void on_pushButton_3_clicked();

private:
    Ui::uiTL1Vacuum *ui;
    ValvesWindow* globalValves;
};

#endif // UITL1VACUUM_H
