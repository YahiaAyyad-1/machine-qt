#ifndef VALVES_WINDOW_H
#define VALVES_WINDOW_H

#include <QMainWindow>

#include "macros.h"
#include "client.h"
#include "widgets/valve_widget.h"

namespace Ui {
class ValvesWindow;
}

class ValvesWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ValvesWindow(QWidget *parent = nullptr);
    ~ValvesWindow();

private slots:
    void on_btnReset_clicked();

    void on_btnOpenAll_clicked();

    void on_btnCloseAll_clicked();

    void onMachineStatusValueChanged(const QVariant&);

private:
    Ui::ValvesWindow *ui;

    QEpicsPV* machineStatus;
};

#endif // VALVES_WINDOW_H
