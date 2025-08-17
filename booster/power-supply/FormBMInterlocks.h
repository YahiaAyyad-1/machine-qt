#ifndef FORMBMINTERLOCKS_H
#define FORMBMINTERLOCKS_H

#include <QMainWindow>

namespace Ui {
class FormBMInterlocks;
}

class FormBMInterlocks : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormBMInterlocks(QWidget *parent = 0);
    ~FormBMInterlocks();

private:
    Ui::FormBMInterlocks *ui;
};

#endif // FORMBMINTERLOCKS_H
