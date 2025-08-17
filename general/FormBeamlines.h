#ifndef FORMBEAMLINES_H
#define FORMBEAMLINES_H

#include <QMainWindow>

#include "FormBeamlinesInterlocks.h"
#include "macros.h"
#include "client.h"

#include <qepicspv.h>

#define BL_VALVES_COUNT    7
#define NUMBER(X) \
    QString::number(X) \

namespace Ui {
class FormBeamlines;
}

class FormBeamlines : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormBeamlines(QWidget *parent = 0);
    ~FormBeamlines();

private slots:
    void valveStateChanged();

    void on_btnInterlocks_clicked();

    void on_btnReset_clicked();

private:
    Ui::FormBeamlines *ui;

    FormBeamlinesInterlocks* interlocks;

    QEpicsPV* pvs[BL_VALVES_COUNT * 2];
};

#endif // FORMBEAMLINES_H
