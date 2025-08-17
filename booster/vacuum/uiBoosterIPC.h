#ifndef UIBOOSTERIPC_H
#define UIBOOSTERIPC_H

#include <QMainWindow>

namespace Ui {
class uiBoosterIPC;
}

class uiBoosterIPC : public QMainWindow
{
    Q_OBJECT

public:
    explicit uiBoosterIPC(QWidget *parent = 0);
    ~uiBoosterIPC();

private slots:
    void on_btnEnableInterlocks_clicked();

    void on_btnDisableInterlocks_clicked();

private:
    Ui::uiBoosterIPC *ui;
};

#endif // UIBOOSTERIPC_H
