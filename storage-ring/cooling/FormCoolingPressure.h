#ifndef FORMCOOLINGPRESSURE_H
#define FORMCOOLINGPRESSURE_H

#include <QMainWindow>
#include "macros.h"

namespace Ui {
class FormCoolingPressure;
}

class FormCoolingPressure : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormCoolingPressure(QWidget *parent = 0);
    ~FormCoolingPressure();

private:
    Ui::FormCoolingPressure *ui;
};

#endif // FORMCOOLINGPRESSURE_H
