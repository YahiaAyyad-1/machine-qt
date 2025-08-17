#ifndef TIMING_WINDOW_H
#define TIMING_WINDOW_H

#include <QMainWindow>
#include "widgets/pulser_widget.h"
#include "widgets/delayed_pulser_widget.h"
#include "widgets/cml_output_widget.h"
#include "widgets/ttl_output_widget.h"
#include "widgets/universal_output_widget.h"
#include "widgets/prescaler_widget.h"

#define PULSERS_COUNT   14

namespace Ui {
class EventReceiverWindow;
}

class EventReceiverWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EventReceiverWindow(int evr, QWidget *parent = nullptr);
    ~EventReceiverWindow();

private:
    Ui::EventReceiverWindow *ui;

    QString prefix;
};

#endif // TIMING_WINDOW_H
