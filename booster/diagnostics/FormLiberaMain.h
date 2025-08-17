#ifndef FORMLIBERAMAIN_H
#define FORMLIBERAMAIN_H

#include <QMainWindow>

#include "FormLiberaControl.h"

namespace Ui {
class FormLiberaMain;
}

class FormLiberaMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormLiberaMain(QWidget *parent = 0);
    ~FormLiberaMain();

private slots:
    void on_btnConfiguration_clicked();

private:
    Ui::FormLiberaMain *ui;

    FormLiberaControl* control;
};

#endif // FORMLIBERAMAIN_H
