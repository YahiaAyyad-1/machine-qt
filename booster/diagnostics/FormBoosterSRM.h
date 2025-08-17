#ifndef FORMBOOSTERSRM_H
#define FORMBOOSTERSRM_H

#include <QMainWindow>

namespace Ui {
class FormBoosterSRM;
}

class FormBoosterSRM : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormBoosterSRM(QWidget *parent = 0);
    ~FormBoosterSRM();

private:
    Ui::FormBoosterSRM *ui;
};

#endif // FORMBOOSTERSRM_H
