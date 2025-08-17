#ifndef FORMAFG_H
#define FORMAFG_H

#include <QMainWindow>

namespace Ui {
class FormAFG;
}

class FormAFG : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormAFG(QWidget *parent = 0);
    ~FormAFG();

private:
    Ui::FormAFG *ui;
};

#endif // FORMAFG_H
