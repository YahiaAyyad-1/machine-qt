#ifndef LIBERA_SPARK_WINDOW_H
#define LIBERA_SPARK_WINDOW_H

#include <QMainWindow>
#include "libera_spark_data_window.h"
#include "macros.h"

namespace Ui {
class LiberaSparkWindow;
}

class LiberaSparkWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LiberaSparkWindow(QWidget *parent = nullptr);
    ~LiberaSparkWindow();

private slots:
    void on_btnADC_clicked();

    void on_btnTBTIQ_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_14_clicked();

private:
    Ui::LiberaSparkWindow *ui;

    LiberaSparkDataWindow* data;
};

#endif // LIBERA_SPARK_WINDOW_H
