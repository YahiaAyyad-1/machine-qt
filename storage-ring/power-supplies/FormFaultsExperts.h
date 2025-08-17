#ifndef FORMFAULTSEXPERTS_H
#define FORMFAULTSEXPERTS_H

#include <QMainWindow>
#include "macros.h"

namespace Ui {
class FormFaultsExperts;
}

class FormFaultsExperts : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormFaultsExperts(QString group, QWidget *parent = 0);
    ~FormFaultsExperts();

private:
    Ui::FormFaultsExperts *ui;

    QString group;
};

#endif // FORMFAULTSEXPERTS_H
