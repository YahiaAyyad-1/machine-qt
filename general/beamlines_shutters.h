#ifndef BEAMLINES_SHUTTERS_H
#define BEAMLINES_SHUTTERS_H

#include <QMainWindow>
#include "macros.h"
namespace Ui {
class beamlines_shutters;
}

class beamlines_shutters : public QMainWindow
{
    Q_OBJECT


public:
    explicit beamlines_shutters(QWidget *parent = nullptr);
    ~beamlines_shutters();

private:
    Ui::beamlines_shutters *ui;
};

#endif // BEAMLINES_SHUTTERS_H
