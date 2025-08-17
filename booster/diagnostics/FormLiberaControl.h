#ifndef FORMLIBERACONTROL_H
#define FORMLIBERACONTROL_H

#include <QMainWindow>

namespace Ui {
class FormLiberaControl;
}

class FormLiberaControl : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormLiberaControl(QWidget *parent = 0);
    ~FormLiberaControl();

private:
    Ui::FormLiberaControl *ui;
};

#endif // FORMLIBERACONTROL_H
