#ifndef UNIVERSAL_OUTPUT_WIDGET_H
#define UNIVERSAL_OUTPUT_WIDGET_H

#include <QWidget>

namespace Ui {
class UniversalOutputWidget;
}

class UniversalOutputWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UniversalOutputWidget(QString prefix, QWidget *parent = nullptr);
    ~UniversalOutputWidget();

private:
    Ui::UniversalOutputWidget *ui;

    QString prefix;
};

#endif // UNIVERSAL_OUTPUT_WIDGET_H
