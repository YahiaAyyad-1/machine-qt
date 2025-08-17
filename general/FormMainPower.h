#ifndef FORMMAINPOWER_H
#define FORMMAINPOWER_H

#include <QMainWindow>
#include "FormMainPowerDetails.h"
#include "macros.h"

namespace Ui {
class FormMainPower;
}

class FormMainPower : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormMainPower(QWidget *parent = 0);
    ~FormMainPower();

private slots:
    void on_btnDetails_clicked();

private:
    Ui::FormMainPower *ui;

    FormMainPowerDetails* detailsWindow;
};

#endif // FORMMAINPOWER_H
