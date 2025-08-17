#include "delayed_pulser_widget.h"
#include "ui_delayed_pulser_widget.h"

DelayedPulserWidget::DelayedPulserWidget(QString prefix, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DelayedPulserWidget)
{
    ui->setupUi(this);

    this->prefix = prefix;
    ui->ledEnabled->setVariableNameSubstitutionsProperty("group=" + this->prefix);
    ui->lblName->setVariableNameSubstitutionsProperty("group=" + this->prefix);
    ui->lblDelay->setVariableNameSubstitutionsProperty("group=" + this->prefix);
    ui->lblWidth->setVariableNameSubstitutionsProperty("group=" + this->prefix);
    ui->lblPrescaler->setVariableNameSubstitutionsProperty("group=" + this->prefix);
    ui->txtDelay->setVariableNameSubstitutionsProperty("group=" + this->prefix);
    ui->txtWidth->setVariableNameSubstitutionsProperty("group=" + this->prefix);
    ui->txtPrescaler->setVariableNameSubstitutionsProperty("group=" + this->prefix);
    ui->btnOFF->setVariableNameSubstitutionsProperty("group=" + this->prefix);
    ui->btnON->setVariableNameSubstitutionsProperty("group=" + this->prefix);
}

DelayedPulserWidget::~DelayedPulserWidget()
{
    delete ui;
}
