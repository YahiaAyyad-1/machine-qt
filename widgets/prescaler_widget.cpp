#include "prescaler_widget.h"
#include "ui_prescaler_widget.h"

PrescalerWidget::PrescalerWidget(QString prefix, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrescalerWidget)
{
    ui->setupUi(this);

    this->prefix = prefix;
    ui->lblName->setVariableNameSubstitutionsProperty("group=" + this->prefix);
    ui->lblPrescaler->setVariableNameSubstitutionsProperty("group=" + this->prefix);
    ui->txtPrescaler->setVariableNameSubstitutionsProperty("group=" + this->prefix);
}

PrescalerWidget::~PrescalerWidget()
{
    delete ui;
}
