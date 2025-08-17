#ifndef FORMBOOSTERCORRECTORS_H
#define FORMBOOSTERCORRECTORS_H

#include <QMainWindow>

namespace Ui {
class FormBoosterCorrectors;
}

class FormBoosterCorrectors : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormBoosterCorrectors(QWidget *parent = 0);
    ~FormBoosterCorrectors();

private slots:
    void enableButtons_Clicked();

private:
    Ui::FormBoosterCorrectors *ui;
};

#endif // FORMBOOSTERCORRECTORS_H
