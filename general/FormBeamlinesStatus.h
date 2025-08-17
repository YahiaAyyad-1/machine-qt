#ifndef FORMBEAMLINESSTATUS_H
#define FORMBEAMLINESSTATUS_H

#include <QMainWindow>
#include "macros.h"
namespace Ui {
class FormBeamlinesStatus;
}

class FormBeamlinesStatus : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormBeamlinesStatus(QWidget *parent = nullptr);
    ~FormBeamlinesStatus();

private:
    Ui::FormBeamlinesStatus *ui;
};

#endif // FORMBEAMLINESSTATUS_H
