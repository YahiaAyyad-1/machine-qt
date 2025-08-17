#include "FormIOCLimits.h"
#include "ui_FormIOCLimits.h"

FormIOCLimits::FormIOCLimits(QString group, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormIOCLimits)
{
    ui->setupUi(this);
    this->group = group;
    this->ui->lblTitle->setText(this->group + " Limits");
    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));

    foreach (QELabel* label, this->findChildren<QELabel*>())
    {
        label->setVariableNameSubstitutionsProperty("group=" + this->group);
    }

    foreach (QELineEdit* text, this->findChildren<QELineEdit*>())
    {
        text->setVariableNameSubstitutionsProperty("group=" + this->group);
    }
}

FormIOCLimits::~FormIOCLimits()
{
    delete ui;
}
