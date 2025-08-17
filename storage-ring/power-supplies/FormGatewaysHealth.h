#ifndef FORMGATEWAYSHEALTH_H
#define FORMGATEWAYSHEALTH_H

#include <QMainWindow>

#include <qepicspv.h>

namespace Ui {
class FormGatewaysHealth;
}

class FormGatewaysHealth : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormGatewaysHealth(QWidget *parent = 0);
    ~FormGatewaysHealth();

private slots:
    void loadChanged();

    void freeRAMChanged();

private:
    Ui::FormGatewaysHealth *ui;
    QEpicsPV* pvGwLoad[6];
    QEpicsPV* pvGwFreeRAM[6];
};

#endif // FORMGATEWAYSHEALTH_H
