#include "ttl_output_widget.h"
#include "ui_ttl_output_widget.h"

TTLOutputWidget::TTLOutputWidget(QString prefix, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TTLOutputWidget)
{
    ui->setupUi(this);

    this->prefix = prefix;
    ui->lblName->setVariableNameSubstitutionsProperty("group=" + this->prefix);
    ui->lblOutput->setVariableNameSubstitutionsProperty("group=" + this->prefix);
    ui->cbOutput->setVariableNameSubstitutionsProperty("group=" + this->prefix);
}

TTLOutputWidget::~TTLOutputWidget()
{
    delete ui;
}
