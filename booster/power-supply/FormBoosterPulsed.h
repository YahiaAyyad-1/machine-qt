#ifndef FORMBOOSTERPULSED_H
#define FORMBOOSTERPULSED_H

#include <QMainWindow>
#include <qepicspv.h>

namespace Ui {
class FormBoosterPulsed;
}

class FormBoosterPulsed : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormBoosterPulsed(QWidget *parent = 0);
    ~FormBoosterPulsed();

private slots:
    void kickerVoltage_Changed();

private:
    Ui::FormBoosterPulsed *ui;
    QEpicsPV* pvKickerVoltage;
};

#endif // FORMBOOSTERPULSED_H
