#ifndef PULSER_WIDGET_H
#define PULSER_WIDGET_H

#include <QWidget>

namespace Ui {
class PulserWidget;
}

class PulserWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PulserWidget(QString prefix, QWidget *parent = nullptr);
    ~PulserWidget();

private:
    Ui::PulserWidget *ui;

    QString prefix;
};

#endif // PULSER_WIDGET_H
