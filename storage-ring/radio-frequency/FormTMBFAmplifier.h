#ifndef FORMTMBFAMPLIFIER_H
#define FORMTMBFAMPLIFIER_H

#include <QMainWindow>
#include "macros.h"

namespace Ui {
class FormTMBFAmplifier;
}

class FormTMBFAmplifier : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormTMBFAmplifier(QWidget *parent = 0);
    ~FormTMBFAmplifier();

private:
    Ui::FormTMBFAmplifier *ui;
};

#endif // FORMTMBFAMPLIFIER_H
