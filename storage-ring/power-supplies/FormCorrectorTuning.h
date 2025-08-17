#ifndef FORMCORRECTORTUNING_H
#define FORMCORRECTORTUNING_H

#include <QMainWindow>

namespace Ui {
class FormCorrectorTuning;
}

class FormCorrectorTuning : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormCorrectorTuning(QString group, QWidget *parent = 0);
    ~FormCorrectorTuning();

private:
    Ui::FormCorrectorTuning *ui;

    QString group;
};

#endif // FORMCORRECTORTUNING_H
