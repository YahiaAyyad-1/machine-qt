#ifndef DELAYED_PULSER_WIDGET_H
#define DELAYED_PULSER_WIDGET_H

#include <QWidget>

namespace Ui {
class DelayedPulserWidget;
}

class DelayedPulserWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DelayedPulserWidget(QString prefix, QWidget *parent = nullptr);
    ~DelayedPulserWidget();

private:
    Ui::DelayedPulserWidget *ui;

    QString prefix;
};

#endif // DELAYED_PULSER_WIDGET_H
