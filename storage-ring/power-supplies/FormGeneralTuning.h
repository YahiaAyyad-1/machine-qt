#ifndef FORMGENERALTUNING_H
#define FORMGENERALTUNING_H

#include <QMainWindow>

#include "macros.h"
#include "client.h"

namespace Ui {
class FormGeneralTuning;
}

class FormGeneralTuning : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormGeneralTuning(QString magnet, QWidget *parent = 0);
    ~FormGeneralTuning();

    void setValue(QString command, float value);
    void setValue(QString command, int value);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

private:
    Ui::FormGeneralTuning *ui;

    QString magnet;
};

#endif // FORMGENERALTUNING_H
