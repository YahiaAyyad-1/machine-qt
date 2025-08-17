#include "ioc_manager_widget.h"
#include "ui_ioc_manager_widget.h"

IOCManagerWidget::IOCManagerWidget(QString prefix, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IOCManagerWidget)
{
    ui->setupUi(this);

    ui->lblName->setText(prefix);
    ui->lblTOD->setVariableNameSubstitutionsProperty("group=" + prefix);
    ui->lblUptime->setVariableNameSubstitutionsProperty("group=" + prefix);
    ui->lblFreeMem->setVariableNameSubstitutionsProperty("group=" + prefix);
    ui->lblLoadIOC->setVariableNameSubstitutionsProperty("group=" + prefix);
    ui->lblLoadSystem->setVariableNameSubstitutionsProperty("group=" + prefix);
    ui->ledStatus->setVariableNameSubstitutionsProperty("group=" + prefix);

    this->stats = nullptr;
    QObject::connect(this->ui->btnDetails, &QPushButton::clicked, this, [this, prefix](bool checked) {
        Q_UNUSED(checked);
        this->stats = new FormIOCStats(prefix, this);
        this->stats->show();
    });
}

IOCManagerWidget::~IOCManagerWidget()
{
    delete ui;
}
