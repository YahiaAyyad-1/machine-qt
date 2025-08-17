#include "cml_output_widget.h"
#include "ui_cml_output_widget.h"

CmlOutputWidget::CmlOutputWidget(QString prefix, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CmlOutputWidget)
{
    ui->setupUi(this);

    this->prefix = prefix;
    ui->ledEnabled->setVariableNameSubstitutionsProperty("group=" + this->prefix);
    ui->lblName->setVariableNameSubstitutionsProperty("group=" + this->prefix);
    ui->lblPrescaler->setVariableNameSubstitutionsProperty("group=" + this->prefix);
    ui->txtPrescaler->setVariableNameSubstitutionsProperty("group=" + this->prefix);
    ui->btnOFF->setVariableNameSubstitutionsProperty("group=" + this->prefix);
    ui->btnON->setVariableNameSubstitutionsProperty("group=" + this->prefix);
}

CmlOutputWidget::~CmlOutputWidget()
{
    delete ui;
}
