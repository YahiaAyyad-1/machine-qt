#include "uiSR_RFCurrent.h"
#include "ui_uiSR_RFCurrent.h"
#include <qwt_dial_needle.h>
#include <qwt_dial.h>

uiSR_RFCurrent::uiSR_RFCurrent(QWidget *parent,QString ssa) :
    QMainWindow(parent),
    ui(new Ui::uiSR_RFCurrent)
{
    ui->setupUi(this);
    //set $(ssa) for title
    QString title=ui->title_label->text();
    ui->title_label->setText(title.replace("$(ssa)",ssa));

    QString Pre_DriverPower_FWD="SRC03-RF-SSA$(ssa)-DIS00:getUpperForwardPower";
    pvFWDPower=new QEpicsPV(Pre_DriverPower_FWD.replace("$(ssa)",ssa));

    QString Pre_DriverPower_RFL="SRC03-RF-SSA$(ssa)-DIS00:getUpperReflectedPower";
    pvRFLPower=new QEpicsPV(Pre_DriverPower_RFL.replace("$(ssa)",ssa));
    QObject::connect(pvFWDPower, SIGNAL(valueChanged(QVariant)), this, SLOT(preDriverPower_Changed()));
    QObject::connect(pvRFLPower, SIGNAL(valueChanged(QVariant)), this, SLOT(preDriverPower_Changed()));

    QString substitutions = "";
    foreach (QELabel* w, this->findChildren<QELabel*>()) {
        substitutions = w->getVariableNameSubstitutionsProperty();
        substitutions += ",ssa=" + ssa;
        w->setVariableNameSubstitutionsProperty(substitutions);
    }

    foreach (QEPushButton* w, this->findChildren<QEPushButton*>()) {
        substitutions = w->getVariableNameSubstitutionsProperty();
        substitutions += ",ssa=" + ssa;
        w->setVariableNameSubstitutionsProperty(substitutions);
    }

    foreach (QESimpleShape* w, this->findChildren<QESimpleShape*>()) {
        substitutions = w->getVariableNameSubstitutionsProperty();
        substitutions += ",ssa=" + ssa;
        w->setVariableNameSubstitutionsProperty(substitutions);
    }

    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
}

uiSR_RFCurrent::~uiSR_RFCurrent()
{
    delete ui;
}

//check Dial Amplifier Power
void uiSR_RFCurrent::preDriverPower_Changed(){

    //set the value for Dial Forwarded Amplifier Power
    QwtDialSimpleNeedle* needle = new QwtDialSimpleNeedle(QwtDialSimpleNeedle::Arrow);
    ui->Forward_Amplifier_Power->setNeedle(needle);
    ui->Forward_Amplifier_Power->setValue(pvFWDPower->get().toDouble());
    ui->label_FWD_AmplifierPower->setText(QString::number(pvFWDPower->get().toDouble()));

    //set the value for Dial Reflected Amplifier Power
    QwtDialSimpleNeedle* needle2 = new QwtDialSimpleNeedle(QwtDialSimpleNeedle::Arrow);
    ui->Reflected_AmplifierPower->setNeedle(needle2);
    ui->Reflected_AmplifierPower->setValue(pvRFLPower->get().toDouble());
    ui->label_RFL_AmplifierPower->setText(QString::number(pvRFLPower->get().toDouble()));
}
