#ifndef UISRHEATABSORBERS_H
#define UISRHEATABSORBERS_H

#include <QMainWindow>
#include "client.h"

namespace Ui {
class uiSRHeatAbsorbers;
}

class uiSRHeatAbsorbers : public QMainWindow
{
    Q_OBJECT

public:
    explicit uiSRHeatAbsorbers(QWidget *parent = 0);
    ~uiSRHeatAbsorbers();

private slots:
    void on_btnClose_clicked();

private:
    Ui::uiSRHeatAbsorbers *ui;
};

#endif // UISRHEATABSORBERS_H
