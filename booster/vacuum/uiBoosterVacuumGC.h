#ifndef UIBOOSTERVACUUMGC_H
#define UIBOOSTERVACUUMGC_H

#include <QMainWindow>

namespace Ui {
class uiBoosterVacuumGC;
}

class uiBoosterVacuumGC : public QMainWindow
{
    Q_OBJECT

public:
    explicit uiBoosterVacuumGC(QWidget *parent = 0);
    ~uiBoosterVacuumGC();

private:
    Ui::uiBoosterVacuumGC *ui;
};

#endif // UIBOOSTERVACUUMGC_H
