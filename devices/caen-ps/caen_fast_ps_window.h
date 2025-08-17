#ifndef CAEN_FAST_PS_WINDOW_H
#define CAEN_FAST_PS_WINDOW_H

#include <QMainWindow>
#include "macros.h"

namespace Ui {
class CaenFastPSWindow;
}

class CaenFastPSWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CaenFastPSWindow(QString group, QWidget *parent = 0);
    ~CaenFastPSWindow();

private:
    Ui::CaenFastPSWindow *ui;

    QString group;
};

#endif // FORMID09FASTPS_H
