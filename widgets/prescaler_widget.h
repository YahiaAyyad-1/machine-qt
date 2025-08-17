#ifndef PRESCALER_WIDGET_H
#define PRESCALER_WIDGET_H

#include <QWidget>

namespace Ui {
class PrescalerWidget;
}

class PrescalerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PrescalerWidget(QString prefix, QWidget *parent = nullptr);
    ~PrescalerWidget();

private:
    Ui::PrescalerWidget *ui;

    QString prefix;
};

#endif // PRESCALER_WIDGET_H
