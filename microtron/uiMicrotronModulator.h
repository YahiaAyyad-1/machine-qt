#ifndef UIMICROTRONMODULATOR_H
#define UIMICROTRONMODULATOR_H

#include <QMainWindow>

namespace Ui {
class uiMicrotronModulator;
}

class uiMicrotronModulator : public QMainWindow
{
    Q_OBJECT

public:
    explicit uiMicrotronModulator(QWidget *parent = 0);
    ~uiMicrotronModulator();

private:
    Ui::uiMicrotronModulator *ui;
};

#endif // UIMICROTRONMODULATOR_H
