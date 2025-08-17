#ifndef VACUUM_CELL_WIDGET_H
#define VACUUM_CELL_WIDGET_H

#include <QWidget>

namespace Ui {
class VacuumCellWidget;
}

class VacuumCellWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VacuumCellWidget(int cell, char section, QWidget *parent = nullptr);
    ~VacuumCellWidget();

private:
    Ui::VacuumCellWidget *ui;
};

#endif // VACUUM_CELL_WIDGET_H
