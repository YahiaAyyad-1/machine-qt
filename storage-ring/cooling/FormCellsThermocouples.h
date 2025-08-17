#ifndef FORMCELLSTHERMOCOUPLES_H
#define FORMCELLSTHERMOCOUPLES_H

#include <QMainWindow>
#include "widgets/sr_cooling_thermocouple_widget.h"

namespace Ui {
class FormCellsThermocouples;
}

class FormCellsThermocouples : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormCellsThermocouples(QWidget *parent = 0);
    ~FormCellsThermocouples();

private:
    Ui::FormCellsThermocouples *ui;
};

#endif // FORMCELLSTHERMOCOUPLES_H
