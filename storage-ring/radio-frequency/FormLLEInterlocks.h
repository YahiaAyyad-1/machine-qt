#ifndef FORMLLEINTERLOCKS_H
#define FORMLLEINTERLOCKS_H

#include <QMainWindow>

namespace Ui {
class FormLLEInterlocks;
}

class FormLLEInterlocks : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormLLEInterlocks(QWidget *parent = 0);
    ~FormLLEInterlocks();

private:
    Ui::FormLLEInterlocks *ui;
};

#endif // FORMLLEINTERLOCKS_H
