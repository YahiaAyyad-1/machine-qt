#ifndef FORMPICOPOSITION_H
#define FORMPICOPOSITION_H

#include <QMainWindow>

namespace Ui {
class FormPicoPosition;
}

class FormPicoPosition : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormPicoPosition(QWidget *parent = nullptr);
    ~FormPicoPosition();

private:
    Ui::FormPicoPosition *ui;
};

#endif // FORMPICOPOSITION_H
