#ifndef FORMDCINTERLOCKS_H
#define FORMDCINTERLOCKS_H

#include <QMainWindow>

namespace Ui {
class FormDCInterlocks;
}

class FormDCInterlocks : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormDCInterlocks(QString magnet, QWidget *parent = 0);
    ~FormDCInterlocks();

private:
    Ui::FormDCInterlocks *ui;

    QString magnet;
};

#endif // FORMDCINTERLOCKS_H
