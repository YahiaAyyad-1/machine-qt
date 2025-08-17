#ifndef FORMBEATSPICOAMMETER_H
#define FORMBEATSPICOAMMETER_H

#include <QMainWindow>
#include "qepicspv.h"
#include "client.h"
#include "macros.h"
#include "formpicoplot.h"
#include "formpicoposition.h"
#include "formpicoplotoffset.h"

namespace Ui {
class FormBeatsPicoammeter;
}

class FormBeatsPicoammeter : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormBeatsPicoammeter(QWidget *parent = nullptr);
    ~FormBeatsPicoammeter();
private slots:

    void checkActiveChannels();

    void checkScanRate();

    void on_pushButton_clicked();

    void on_btnPlotPosition_clicked();


    void on_btnChOffset_clicked();

private:
    Ui::FormBeatsPicoammeter *ui;
    QEpicsPV* activeChannels;
    QEpicsPV* scanRate;

    FormPicoPlot* plot;
    FormPicoPosition* plotPosition;
    FormPicoPlotOffset* plotOffset;
};

#endif // FORMBEATSPICOAMMETER_H
