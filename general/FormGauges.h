#ifndef FORMGAUGES_H
#define FORMGAUGES_H

#include <QMainWindow>

namespace Ui {
class FormGauges;
}

class FormGauges : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormGauges(QWidget *parent = nullptr);
    ~FormGauges();

private slots:
    void on_btnReset_clicked();

private:
    Ui::FormGauges *ui;
};

#endif // FORMGAUGES_H
