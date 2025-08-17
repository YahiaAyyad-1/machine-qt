#ifndef FORMFILLING_H
#define FORMFILLING_H

#include <QMainWindow>

namespace Ui {
class FormFilling;
}

class FormFilling : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormFilling(QWidget *parent = 0);
    ~FormFilling();

private:
    Ui::FormFilling *ui;
};

#endif // FORMFILLING_H
