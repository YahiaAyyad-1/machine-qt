#ifndef UISRGAUGEINTERLOCKS_H
#define UISRGAUGEINTERLOCKS_H

#include <QMainWindow>

namespace Ui {
class uiSRGaugeInterlocks;
}

class uiSRGaugeInterlocks : public QMainWindow
{
    Q_OBJECT

public:
    explicit uiSRGaugeInterlocks(QWidget *parent = 0);
    ~uiSRGaugeInterlocks();

private slots:
    void on_btnClose_clicked();

private:
    Ui::uiSRGaugeInterlocks *ui;
};

#endif // UISRGAUGEINTERLOCKS_H
