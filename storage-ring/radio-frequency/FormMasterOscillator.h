#ifndef FORMMASTEROSCILLATOR_H
#define FORMMASTEROSCILLATOR_H

#include <QMainWindow>

#include "client.h"

namespace Ui {
class FormMasterOscillator;
}

class FormMasterOscillator : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormMasterOscillator(QWidget *parent = 0);
    ~FormMasterOscillator();

private slots:
    void on_btnON_clicked();

private:
    Ui::FormMasterOscillator *ui;
};

#endif // FORMMASTEROSCILLATOR_H
