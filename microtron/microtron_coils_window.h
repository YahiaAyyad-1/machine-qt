#ifndef MICROTRON_COILS_WINDOW_H
#define MICROTRON_COILS_WINDOW_H

#include <QMainWindow>
#include "widgets/caen_ps_widget.h"
#include "macros.h"

namespace Ui {
class MicrotronCoilsWindow;
}

class MicrotronCoilsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MicrotronCoilsWindow(QWidget *parent = nullptr);
    ~MicrotronCoilsWindow();

private:
    Ui::MicrotronCoilsWindow *ui;
};

#endif // MICROTRON_COILS_WINDOW_H
