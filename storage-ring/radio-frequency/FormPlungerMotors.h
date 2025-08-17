#ifndef FORMPLUNGERMOTORS_H
#define FORMPLUNGERMOTORS_H
#include "macros.h"
#include <QMainWindow>

namespace Ui {
class FormPlungerMotors;
}

class FormPlungerMotors : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormPlungerMotors(QWidget *parent = nullptr);
    ~FormPlungerMotors();

private:
    Ui::FormPlungerMotors *ui;
};

#endif // FORMPLUNGERMOTORS_H
