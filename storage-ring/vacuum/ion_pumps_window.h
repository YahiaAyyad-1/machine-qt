#ifndef ION_PUMPS_WINDOW_H
#define ION_PUMPS_WINDOW_H

#include <QMainWindow>
#include "widgets/ion_pump_widget.h"

namespace Ui {
class IonPumpsWindow;
}

class IonPumpsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit IonPumpsWindow(QWidget *parent = nullptr);
    ~IonPumpsWindow();

private:
    Ui::IonPumpsWindow *ui;
};

#endif // ION_PUMPS_WINDOW_H
