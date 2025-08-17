#include "uiSR_RFInterlocks.h"
#include "ui_uiSR_RFInterlocks.h"

uiSR_RFInterlocks::uiSR_RFInterlocks(QWidget *parent,QString ssa) :
    QMainWindow(parent),
    ui(new Ui::uiSR_RFInterlocks)
{
    ui->setupUi(this);
    this->ssa = ssa;

    //set $(ssa) for Title
    QString title = ui->title_label->text().replace("$(ssa)",ssa);
    ui->title_label->setText(title);

    QString substitutions;
    foreach (QESimpleShape* w, this->findChildren<QESimpleShape*>()) {
        substitutions = w->getVariableNameSubstitutionsProperty();
        substitutions += ",ssa=" + ssa;
        w->setVariableNameSubstitutionsProperty(substitutions);
    }
}

uiSR_RFInterlocks::~uiSR_RFInterlocks()
{
    delete ui;
}

void uiSR_RFInterlocks::on_btnClose_clicked()
{
    close();
}

void uiSR_RFInterlocks::on_btnReset_clicked()
{
    for(int i = 0; i <= 10; i++)
    {
        Client::writePV(QString::asprintf("SRC03-RF-SSA%d-DIS%02d:resetInterlocks", this->ssa.toInt(), i), 1);
    }
}
