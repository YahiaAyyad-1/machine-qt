#ifndef FORMSRMTHALES_H
#define FORMSRMTHALES_H

#include <QMainWindow>
#include "macros.h"
namespace Ui {
class FormSrmThales;
}

class FormSrmThales : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormSrmThales(QWidget *parent = nullptr);
    ~FormSrmThales();

private:
    Ui::FormSrmThales *ui;
};

#endif // FORMSRMTHALES_H
