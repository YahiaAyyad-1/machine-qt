#ifndef FORMCORRECTORSREADINGS_H
#define FORMCORRECTORSREADINGS_H

#include <QMainWindow>

#include "macros.h"

namespace Ui {
class FormCorrectorsReadings;
}

class FormCorrectorsReadings : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormCorrectorsReadings(QString group, QWidget *parent = nullptr);
    ~FormCorrectorsReadings();

private:
    Ui::FormCorrectorsReadings *ui;

    QString group;
};

#endif // FORMCORRECTORSREADINGS_H
