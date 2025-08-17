#ifndef FORMFEEDFORWARDSTATUS_H
#define FORMFEEDFORWARDSTATUS_H

#include <QMainWindow>

namespace Ui {
class FormFeedforwardStatus;
}

class FormFeedforwardStatus : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormFeedforwardStatus(QWidget *parent = nullptr);
    ~FormFeedforwardStatus();

private:
    Ui::FormFeedforwardStatus *ui;
};

#endif // FORMFEEDFORWARDSTATUS_H
