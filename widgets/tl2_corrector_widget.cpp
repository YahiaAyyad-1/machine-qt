#include "tl2_corrector_widget.h"
#include "ui_tl2_corrector_widget.h"

TL2CorrectorWidget::TL2CorrectorWidget(QString name, QString prefix, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TL2CorrectorWidget)
{
    ui->setupUi(this);

    ui->lblTitle->setText(name);
    ui->ledStatus->setVariableNameSubstitutionsProperty("prefix=" + prefix);
    ui->lblVoltage->setVariableNameSubstitutionsProperty("prefix=" + prefix);
    ui->lblCurrent->setVariableNameSubstitutionsProperty("prefix=" + prefix);
    ui->txtCurrent->setVariableNameSubstitutionsProperty("prefix=" + prefix);
    ui->btnON->setVariableNameSubstitutionsProperty("prefix=" + prefix);
    ui->btnOFF->setVariableNameSubstitutionsProperty("prefix=" + prefix);
}

TL2CorrectorWidget::~TL2CorrectorWidget()
{
    delete ui;
}
