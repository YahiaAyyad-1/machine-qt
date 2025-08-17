#ifndef FORMRFCOOLING_H
#define FORMRFCOOLING_H

#include <QMainWindow>
#include <QMessageBox>
#include <QStringList>
#include "client.h"

#include "widgets/thermocouple_widget.h"

namespace Ui {
class FormRFCooling;
}

class FormRFCooling : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormRFCooling(QWidget *parent = nullptr);
    ~FormRFCooling();

private slots:
    void on_btnRfThermocouplesReset_clicked();

private:
    Ui::FormRFCooling *ui;
};

#endif // FORMRFCOOLING_H
