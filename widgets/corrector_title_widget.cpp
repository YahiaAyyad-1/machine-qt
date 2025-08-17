#include "corrector_title_widget.h"
#include "ui_corrector_title_widget.h"

CorrectorTitleWidget::CorrectorTitleWidget(int cell, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CorrectorTitleWidget)
{
    ui->setupUi(this);
    ui->lblTitle->setText("Cell " + QString::number(cell));
}

CorrectorTitleWidget::~CorrectorTitleWidget()
{
    delete ui;
}
