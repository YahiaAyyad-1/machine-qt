#ifndef FORMIOCSTATS_H
#define FORMIOCSTATS_H

#include <QMainWindow>
#include <QDesktopWidget>

#include "iocstats/FormIOCLimits.h"
#include "macros.h"

namespace Ui {
class FormIOCStats;
}

class FormIOCStats : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormIOCStats(QString group, QWidget *parent = 0);
    ~FormIOCStats();

private slots:
    void on_pushButton_clicked();

private:
    Ui::FormIOCStats *ui;

    FormIOCLimits* limits;

    QString group;
};

#endif // FORMIOCSTATS_H
