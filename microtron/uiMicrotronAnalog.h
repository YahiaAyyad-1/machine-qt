#ifndef UIMICROTRONANALOG_H
#define UIMICROTRONANALOG_H

#include <QMainWindow>

namespace Ui {
class uiMicrotronAnalog;
}

class uiMicrotronAnalog : public QMainWindow
{
    Q_OBJECT

public:
    explicit uiMicrotronAnalog(QWidget *parent = 0);
    ~uiMicrotronAnalog();

private:
    Ui::uiMicrotronAnalog *ui;
};

#endif // UIMICROTRONANALOG_H
