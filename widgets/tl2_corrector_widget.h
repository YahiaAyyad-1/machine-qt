#ifndef TL2_CORRECTOR_WIDGET_H
#define TL2_CORRECTOR_WIDGET_H

#include <QWidget>

namespace Ui {
class TL2CorrectorWidget;
}

class TL2CorrectorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TL2CorrectorWidget(QString name, QString prefix, QWidget *parent = nullptr);
    ~TL2CorrectorWidget();

private:
    Ui::TL2CorrectorWidget *ui;
};

#endif // TL2_CORRECTOR_WIDGET_H
