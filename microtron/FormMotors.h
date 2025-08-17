#ifndef FORMMOTORS_H
#define FORMMOTORS_H

#include <QMainWindow>

namespace Ui {
class FormMotors;
}

class FormMotors : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormMotors(QWidget *parent = 0);
    ~FormMotors();

private:
    Ui::FormMotors *ui;
};

#endif // FORMMOTORS_H
