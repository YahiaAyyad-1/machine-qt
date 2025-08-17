#ifndef FORMSHAKERINTERLOCKS_H
#define FORMSHAKERINTERLOCKS_H

#include <QMainWindow>

namespace Ui {
class FormShakerInterlocks;
}

class FormShakerInterlocks : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormShakerInterlocks(QString shaker, QWidget *parent = 0);
    ~FormShakerInterlocks();

private:
    Ui::FormShakerInterlocks *ui;

    QString shaker;
};

#endif // FORMSHAKERINTERLOCKS_H
