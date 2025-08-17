#ifndef FORMBEAMLINESINTERLOCKS_H
#define FORMBEAMLINESINTERLOCKS_H

#include <QMainWindow>
#include "client.h"
namespace Ui {
class FormBeamlinesInterlocks;
}

class FormBeamlinesInterlocks : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormBeamlinesInterlocks(QWidget *parent = 0);
    ~FormBeamlinesInterlocks();

private slots:
    void on_btnIRreset_clicked();

    void on_btnXAFSreset_clicked();

    void on_btnMSreset_clicked();

    void on_btnBEATSreset_clicked();

    void on_btnHESEBreset_clicked();

private:
    Ui::FormBeamlinesInterlocks *ui;
};

#endif // FORMBEAMLINESINTERLOCKS_H
