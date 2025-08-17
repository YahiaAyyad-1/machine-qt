#ifndef FORMSRM_H
#define FORMSRM_H

#include <QMainWindow>
#include <qepicspv.h>

namespace Ui {
class FormSRM;
}

class FormSRM : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormSRM(QMainWindow *parent = 0);
    ~FormSRM();

private slots:

    void onShutterStateChanged();

private:
    Ui::FormSRM *ui;

    QEpicsPV* pvShutterFault;
    QEpicsPV* pvShutterClosed;
    QEpicsPV* pvShutterOpened;
};

#endif // FORMSRM_H
