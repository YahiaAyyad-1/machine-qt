#ifndef FORMTIMEREXPERT_H
#define FORMTIMEREXPERT_H

#include <QMainWindow>
#include "macros.h"
#include "client.h"

namespace Ui {
class FormTimerExpert;
}

class FormTimerExpert : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormTimerExpert(QWidget *parent = nullptr);
    ~FormTimerExpert();

private slots:
    void on_btnAgpsTSreset_clicked();

    void on_btnAgpsTreset_clicked();

    void on_btncathTSreset_clicked();

    void on_btncathTreset_clicked();

private:
    Ui::FormTimerExpert *ui;
};

#endif // FORMTIMEREXPERT_H
