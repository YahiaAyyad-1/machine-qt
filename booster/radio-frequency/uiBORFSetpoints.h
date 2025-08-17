#ifndef UIRFSETPOINTS_H
#define UIRFSETPOINTS_H

#include <QMainWindow>

namespace Ui {
class uiBORFSetpoints;
}

class uiBORFSetpoints : public QMainWindow
{
    Q_OBJECT

public:
    explicit uiBORFSetpoints(QWidget *parent = 0);
    ~uiBORFSetpoints();

private slots:
    void on_btnBlowerOFF_clicked();

    void on_btnBlowerON_clicked();

private:
    Ui::uiBORFSetpoints *ui;
};

#endif // UIRFSETPOINTS_H
