#ifndef FROMFRONTENDBBB_H
#define FROMFRONTENDBBB_H

#include <QMainWindow>

#include "macros.h"

namespace Ui {
class FormFrontEndBBB;
}

class FormFrontEndBBB : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormFrontEndBBB(QWidget *parent = nullptr);
    ~FormFrontEndBBB();

private:
    Ui::FormFrontEndBBB *ui;
};

#endif // FROMFRONTENDBBB_H
