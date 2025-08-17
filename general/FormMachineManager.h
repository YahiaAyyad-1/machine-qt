#ifndef FORMMACHINEMANAGER_H
#define FORMMACHINEMANAGER_H

#include <QMainWindow>
#include <QUiLoader>

#include "iocstats/FormIOCStats.h"
#include "macros.h"
#include "client.h"
#include "widgets/ioc_manager_widget.h"

namespace Ui {
class FormMachineManager;
}

class FormMachineManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormMachineManager(QWidget *parent = 0);
    ~FormMachineManager();

private slots:
    void detailsButtonsClicked();

    void on_pushButton_clicked();

private:
    Ui::FormMachineManager *ui;

    QList<QString> names;

    FormIOCStats* stats;
};

#endif // FORMMACHINEMANAGER_H
