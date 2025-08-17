#include "pulser_widget.h"
#include "ui_pulser_widget.h"

PulserWidget::PulserWidget(QString prefix, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PulserWidget)
{
    ui->setupUi(this);
    this->prefix = prefix;

    ui->ledEnabled->setVariableNameSubstitutionsProperty("group=" + this->prefix);
    ui->lblName->setVariableNameSubstitutionsProperty("group=" + this->prefix);
    ui->lblDelay->setVariableNameSubstitutionsProperty("group=" + this->prefix);
    ui->lblWidth->setVariableNameSubstitutionsProperty("group=" + this->prefix);
    ui->txtBaseDelay->setVariableNameSubstitutionsProperty("group=" + this->prefix);
    ui->txtDelay->setVariableNameSubstitutionsProperty("group=" + this->prefix);
    ui->txtWidth->setVariableNameSubstitutionsProperty("group=" + this->prefix);
    ui->btnOFF->setVariableNameSubstitutionsProperty("group=" + this->prefix);
    ui->btnON->setVariableNameSubstitutionsProperty("group=" + this->prefix);

    if (prefix != "GBL-TI-EVR0-P10" &&
        prefix != "GBL-TI-EVR1-P2"  &&
        prefix != "GBL-TI-EVR1-P8")
    {
        this->ui->txtBaseDelay->hide();
    } else
    {
        this->ui->txtDelay->setDisabled(true);
    }
}

PulserWidget::~PulserWidget()
{
    delete ui;
}
