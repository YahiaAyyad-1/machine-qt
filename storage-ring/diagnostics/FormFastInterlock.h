#ifndef FORMFASTINTERLOCK_H
#define FORMFASTINTERLOCK_H

#include <QMainWindow>

#include "macros.h"
#include "client.h"

namespace Ui {
class FormFastInterlock;
}

class FormFastInterlock : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormFastInterlock(QWidget *parent = 0);
    ~FormFastInterlock();

private slots:
    void on_btnReset_clicked();

private:
    Ui::FormFastInterlock *ui;
};

#endif // FORMFASTINTERLOCK_H
