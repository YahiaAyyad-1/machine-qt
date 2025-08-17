#ifndef CAEN_EASY_PS_WINDOW_H
#define CAEN_EASY_PS_WINDOW_H

#include <QMainWindow>
#include "macros.h"

namespace Ui {
class CaenEasyPSWindow;
}

class CaenEasyPSWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CaenEasyPSWindow(QString group, QWidget *parent = 0);
    ~CaenEasyPSWindow();

private:
    Ui::CaenEasyPSWindow *ui;

    QString group;
};

#endif // FORMID09EASYPS_H
