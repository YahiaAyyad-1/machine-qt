#ifndef FORMGDX_H
#define FORMGDX_H

#include <QMainWindow>

#include "macros.h"
#include "client.h"

namespace Ui {
class FormGDX;
}

class FormGDX : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormGDX(QWidget *parent = 0);
    ~FormGDX();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::FormGDX *ui;
};

#endif // FORMGDX_H
