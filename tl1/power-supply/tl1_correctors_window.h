#ifndef TL1_CORRECTORS_WINDOW_H
#define TL1_CORRECTORS_WINDOW_H

#include <QMainWindow>
#include "widgets/caen_ps_widget.h"

namespace Ui {
class TL1CorrectorsWindow;
}

class TL1CorrectorsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TL1CorrectorsWindow(QWidget *parent = nullptr);
    ~TL1CorrectorsWindow();

private:
    Ui::TL1CorrectorsWindow *ui;

    QString group;
};

#endif // TL1_CORRECTORS_WINDOW_H
