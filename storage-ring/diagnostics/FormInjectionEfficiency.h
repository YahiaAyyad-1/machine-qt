#ifndef FORMINJECTIONEFFICIENCY_H
#define FORMINJECTIONEFFICIENCY_H

#include "macros.h"
#include <QMainWindow>

namespace Ui {
class FormInjectionEfficiency;
}

class FormInjectionEfficiency : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormInjectionEfficiency(QWidget *parent = nullptr);
    ~FormInjectionEfficiency();

private:
    Ui::FormInjectionEfficiency *ui;
};

#endif // FORMINJECTIONEFFICIENCY_H
