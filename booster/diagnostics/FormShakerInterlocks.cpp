#include "FormShakerInterlocks.h"
#include "ui_FormShakerInterlocks.h"

FormShakerInterlocks::FormShakerInterlocks(QString shaker, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormShakerInterlocks)
{
    ui->setupUi(this);
    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
    this->shaker = shaker;
    // ui->mainTitle->setText(this->shaker + " Interlocks");

    QList<QELabel*> labels = this->findChildren<QELabel*>();
    foreach (QELabel* label, labels) {
        label->setVariableNameSubstitutionsProperty("group=" + this->shaker);
    }

    QList<QESimpleShape*> text = this->findChildren<QESimpleShape*>();
    foreach (QESimpleShape* txt, text) {
        txt->setVariableNameSubstitutionsProperty("group=" + this->shaker);
    }
}

FormShakerInterlocks::~FormShakerInterlocks()
{
    delete ui;
}
