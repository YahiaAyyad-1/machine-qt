#ifndef FORMCURRENTLIMIT_H
#define FORMCURRENTLIMIT_H

#include <QMainWindow>
#include "macros.h"
namespace Ui {
class FormCurrentLimit;
}

class FormCurrentLimit : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormCurrentLimit(QWidget *parent = nullptr);
    ~FormCurrentLimit();

private:
    Ui::FormCurrentLimit *ui;
};

#endif // FORMCURRENTLIMIT_H
