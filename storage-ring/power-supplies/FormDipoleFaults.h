#ifndef FORMDIPOLEFAULTS_H
#define FORMDIPOLEFAULTS_H

#include <QMainWindow>

#include "FormDipoleFaultsExpert.h"
#include "macros.h"

namespace Ui {
class FormDipoleFaults;
}

class FormDipoleFaults : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormDipoleFaults(QWidget *parent = 0);
    ~FormDipoleFaults();

private slots:
    void on_btnExpert_clicked();

private:
    Ui::FormDipoleFaults *ui;

    FormDipoleFaultsExpert* expert;
};

#endif // FORMDIPOLEFAULTS_H
