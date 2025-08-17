#ifndef TTL_OUTPUT_WIDGET_H
#define TTL_OUTPUT_WIDGET_H

#include <QWidget>

namespace Ui {
class TTLOutputWidget;
}

class TTLOutputWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TTLOutputWidget(QString prefix, QWidget *parent = nullptr);
    ~TTLOutputWidget();

private:
    Ui::TTLOutputWidget *ui;

    QString prefix;
};

#endif // TTL_OUTPUT_WIDGET_H
