#ifndef FORMRFDIAGNOSTICS_H
#define FORMRFDIAGNOSTICS_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

#include "macros.h"

namespace Ui {
class FormRFDiagnostics;
}

class FormRFDiagnostics : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormRFDiagnostics(QWidget *parent = nullptr);
    ~FormRFDiagnostics();

private slots:
    void on_btnBrowse_clicked();

private:
    Ui::FormRFDiagnostics *ui;
};

#endif // FORMRFDIAGNOSTICS_H
