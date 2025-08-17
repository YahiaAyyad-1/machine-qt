#ifndef FORMBPMHEALTH_H
#define FORMBPMHEALTH_H

#include <QMainWindow>
#include <iostream>

#include "macros.h"

namespace Ui {
class FormBPMHealth;
}

class FormBPMHealth : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormBPMHealth(QWidget *parent = 0);
    ~FormBPMHealth();

public slots:
    void onHealthCheckTimerUpdate();

private:
    Ui::FormBPMHealth *ui;

    QTimer* timer;
};

#endif // FORMBPMHEALTH_H
