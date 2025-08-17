#ifndef FORMPICOPLOT_H
#define FORMPICOPLOT_H

#include <QMainWindow>
#include "macros.h"

namespace Ui {
class FormPicoPlot;
}

class FormPicoPlot : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormPicoPlot(QWidget *parent = nullptr);
    ~FormPicoPlot();

private slots:
    void plot_channel_one(bool checked);

    void plot_channel_two(bool checked);

    void plot_channel_three(bool checked);

    void plot_channel_four(bool checked);


private:
    Ui::FormPicoPlot *ui;
};

#endif // FORMPICOPLOT_H
