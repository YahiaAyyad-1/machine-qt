#ifndef CML_OUTPUT_WIDGET_H
#define CML_OUTPUT_WIDGET_H

#include <QWidget>

namespace Ui {
class CmlOutputWidget;
}

class CmlOutputWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CmlOutputWidget(QString prefix, QWidget *parent = nullptr);
    ~CmlOutputWidget();

private:
    Ui::CmlOutputWidget *ui;

    QString prefix;
};

#endif // CML_OUTPUT_WIDGET_H
