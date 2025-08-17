#ifndef FORMPID_H
#define FORMPID_H

#include <QMainWindow>

#include "../diagnostics/FormDCCTExpert.h"
#include "macros.h"

namespace Ui {
class FormPID;
}

class FormPID : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormPID(QWidget *parent = 0);
    ~FormPID();

private slots:
    void on_btnDMM_clicked();

private:
    Ui::FormPID *ui;

    FormDCCTExpert* dcct;
};

#endif // FORMPID_H
