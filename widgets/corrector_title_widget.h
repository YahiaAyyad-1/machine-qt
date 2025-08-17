#ifndef CORRECTOR_TITLE_WIDGET_H
#define CORRECTOR_TITLE_WIDGET_H

#include <QWidget>

namespace Ui {
class CorrectorTitleWidget;
}

class CorrectorTitleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CorrectorTitleWidget(int cell, QWidget *parent = nullptr);
    ~CorrectorTitleWidget();

private:
    Ui::CorrectorTitleWidget *ui;
};

#endif // CORRECTOR_TITLE_WIDGET_H
