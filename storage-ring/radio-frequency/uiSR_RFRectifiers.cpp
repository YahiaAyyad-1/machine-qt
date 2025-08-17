#include "uiSR_RFRectifiers.h"
#include "ui_uiSR_RFRectifiers.h"

uiSR_RFRectifiers::uiSR_RFRectifiers(QWidget *parent,QString ssa) :
    QMainWindow(parent),
    ui(new Ui::uiSR_RFRectifiers)
{
    ui->setupUi(this);
    ssa_Global=ssa;

    //set $(ssa) for title
    QString title=ui->title_label->text();
    ui->title_label->setText(title.replace("$(ssa)",ssa));

    //set $(ssa) for PA-Voltage line Edit
    ui->lineEditPAVoltage->setVariableNameProperty(
                ui->lineEditPAVoltage->getVariableNameProperty().replace("$(ssa)",ssa));

    QString substitutions;
    foreach (QELabel* w, this->findChildren<QELabel*>()) {
        substitutions = w->getVariableNameSubstitutionsProperty();
        substitutions += ",ssa=" + ssa;
        w->setVariableNameSubstitutionsProperty(substitutions);
    }
}

uiSR_RFRectifiers::~uiSR_RFRectifiers()
{
    delete ui;
}

//Amplifier Voltage Set button
void uiSR_RFRectifiers::on_btnSetAmpVoltage_clicked()
{
    for(int i = 1; i <= 5; i++)
    {
        Client::writePV(QString("SRC03-RF-SSA%1-REC%2:setDcVoltage").arg(ssa_Global).arg(i, 2, QChar('0')),ui->lineEditAmpVoltage->text().toDouble());
    }
}

void uiSR_RFRectifiers::on_btnClose_clicked()
{
    close();
}
