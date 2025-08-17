#ifndef IOC_MANAGER_WIDGET_H
#define IOC_MANAGER_WIDGET_H

#include <QWidget>
#include "iocstats/FormIOCStats.h"

namespace Ui {
class IOCManagerWidget;
}

class IOCManagerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IOCManagerWidget(QString prefix, QWidget *parent = nullptr);
    ~IOCManagerWidget();

private:
    Ui::IOCManagerWidget *ui;

    FormIOCStats* stats;
};

#endif // IOC_MANAGER_WIDGET_H
