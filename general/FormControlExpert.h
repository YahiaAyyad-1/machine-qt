#ifndef FORMCONTROLEXPERT_H
#define FORMCONTROLEXPERT_H

#include <QMainWindow>
#include <general/FormPythonManager.h>
#include "FormPythonManager2.h"
#include "macros.h"

namespace Ui {
class FormControlExpert;
}

class FormControlExpert : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormControlExpert(QWidget *parent = nullptr);
    ~FormControlExpert();

private slots:
    void on_btnPythonManager_clicked();

    void on_btnPythonManager46_clicked();

private:
    Ui::FormControlExpert *ui;

    FormPythonManager* pythonManager;
    FormPythonManager2* pythonManager46;
};

#endif // FORMCONTROLEXPERT_H
