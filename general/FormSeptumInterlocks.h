#ifndef FORMSEPTUMINTERLOCKS_H
#define FORMSEPTUMINTERLOCKS_H

#include <QMainWindow>
#include"macros.h"

namespace Ui {
class FormSeptumInterlocks;
}

class FormSeptumInterlocks : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormSeptumInterlocks(QWidget *parent = nullptr);
    ~FormSeptumInterlocks();

private:
    Ui::FormSeptumInterlocks *ui;
};

#endif // FORMSEPTUMINTERLOCKS_H
