#ifndef FORMSETCURRENT_H
#define FORMSETCURRENT_H

#include <QMainWindow>

namespace Ui {
class FormSetCurrent;
}

class FormSetCurrent : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormSetCurrent(QWidget *parent = nullptr);
    ~FormSetCurrent();

private slots:
    void on_btnClose_clicked();

private:
    Ui::FormSetCurrent *ui;
};

#endif // FORMSETCURRENT_H
