#ifndef FORMTIMER_H
#define FORMTIMER_H

#include <QMainWindow>
#include "macros.h"
#include "FormTimerExpert.h"
#include "general/FormPassword.h"

namespace Ui {
class FormTimer;
}

class FormTimer : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormTimer(QWidget *parent = nullptr);
    ~FormTimer();

private slots:
    void on_btnExpert_clicked();
    void open_timers_expert();

private:
    Ui::FormTimer *ui;
};

#endif // FORMTIMER_H
