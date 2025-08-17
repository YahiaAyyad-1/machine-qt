#ifndef FORMIOCLIMITS_H
#define FORMIOCLIMITS_H

#include <QMainWindow>

namespace Ui {
class FormIOCLimits;
}

class FormIOCLimits : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormIOCLimits(QString group, QWidget *parent = 0);
    ~FormIOCLimits();

private:
    Ui::FormIOCLimits *ui;

    QString group;
};

#endif // FORMIOCLIMITS_H
