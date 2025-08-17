#ifndef FORMDIPOLEFAULTSEXPERT_H
#define FORMDIPOLEFAULTSEXPERT_H

#include <QMainWindow>

#include "macros.h"

namespace Ui {
class FormDipoleFaultsExpert;
}

class FormDipoleFaultsExpert : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormDipoleFaultsExpert(QWidget *parent = 0);
    ~FormDipoleFaultsExpert();

private:
    Ui::FormDipoleFaultsExpert *ui;
};

#endif // FORMDIPOLEFAULTSEXPERT_H
