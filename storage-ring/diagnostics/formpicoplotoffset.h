#ifndef FORMPICOPLOTOFFSET_H
#define FORMPICOPLOTOFFSET_H

#include <QMainWindow>
#include "macros.h"

namespace Ui {
class FormPicoPlotOffset;
}

class FormPicoPlotOffset : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormPicoPlotOffset(QWidget *parent = nullptr);
    ~FormPicoPlotOffset();

private slots:
    void plot_channel_one(bool checked);

    void plot_channel_two(bool checked);

    void plot_channel_three(bool checked);

    void plot_channel_four(bool checked);


private:
    Ui::FormPicoPlotOffset *ui;
};

#endif // FORMPICOPLOTOFFSET_H
