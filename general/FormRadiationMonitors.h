#ifndef FORMRADIATIONMONITORS_H
#define FORMRADIATIONMONITORS_H

#include <QMainWindow>
#include "macros.h"

namespace Ui {
class FormRadiationMonitors;
}

class FormRadiationMonitors : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormRadiationMonitors(QWidget *parent = 0);
    ~FormRadiationMonitors();

private:
    Ui::FormRadiationMonitors *ui;
};

#endif // FORMRADIATIONMONITORS_H
