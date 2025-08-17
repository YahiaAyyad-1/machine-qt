#ifndef FORMCORRECTORPLOTTER_H
#define FORMCORRECTORPLOTTER_H

#include <QMainWindow>

namespace Ui {
class FormCorrectorPlotter;
}

class FormCorrectorPlotter : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormCorrectorPlotter(QString group, QWidget *parent = 0);
    ~FormCorrectorPlotter();

private:
    Ui::FormCorrectorPlotter *ui;

    QString group;
};

#endif // FORMCORRECTORPLOTTER_H
