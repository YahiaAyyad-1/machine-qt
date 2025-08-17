#include "universal_output_widget.h"
#include "ui_universal_output_widget.h"

UniversalOutputWidget::UniversalOutputWidget(QString prefix, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UniversalOutputWidget)
{
    ui->setupUi(this);

    this->prefix = prefix;
    ui->lblName->setVariableNameSubstitutionsProperty("group=" + this->prefix);
    ui->lblOutput->setVariableNameSubstitutionsProperty("group=" + this->prefix);
    ui->cbOutput->setVariableNameSubstitutionsProperty("group=" + this->prefix);
}

UniversalOutputWidget::~UniversalOutputWidget()
{
    delete ui;
}
