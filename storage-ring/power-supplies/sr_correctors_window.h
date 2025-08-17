#ifndef SR_CORRECTORS_WINDOW_H
#define SR_CORRECTORS_WINDOW_H

#include <QMainWindow>
#include "widgets/corrector_ps_widget.h"
#include "widgets/corrector_title_widget.h"
#include "qepicspv.h"

#include "client.h"

namespace Ui {
class RingCorrectorsWindow;
}

class RingCorrectorsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RingCorrectorsWindow(QWidget *parent = nullptr);
    ~RingCorrectorsWindow();

private slots:
    void on_btnOFF_H_clicked();

    void on_btnON_H_clicked();

    void on_btnOFF_V_clicked();

    void on_btnON_V_clicked();

    void on_btnOFF_S_clicked();

    void on_btnON_S_clicked();

    void onMachineStateChanged(QVariant value);


private:
    Ui::RingCorrectorsWindow *ui;

    QEpicsPV* machineMode;

};

#endif // SR_CORRECTORS_WINDOW_H
