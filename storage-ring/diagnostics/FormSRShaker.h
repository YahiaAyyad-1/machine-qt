#ifndef FORMSRSHAKER_H
#define FORMSRSHAKER_H

#include <QMainWindow>

#include "booster/diagnostics/FormShakerInterlocks.h"

namespace Ui {
class FormSRShaker;
}

class FormSRShaker : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormSRShaker(QWidget *parent = 0);
    ~FormSRShaker();

private slots:
    void on_btnClose_clicked();

    void on_btnDetailsCH1_clicked();

    void on_btnDetailsCH2_clicked();

    void on_btnONCH1_clicked();

private:
    Ui::FormSRShaker *ui;

    FormShakerInterlocks* ilk;
};

#endif // FORMSRSHAKER_H
