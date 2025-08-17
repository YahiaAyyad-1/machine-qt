#include "FormAmplifierExpert.h"
#include "ui_FormAmplifierExpert.h"
#include<iostream>
FormAmplifierExpert::FormAmplifierExpert(int ssa, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormAmplifierExpert)
{
    ui->setupUi(this);
    CONNECT_CLOSE_BUTTON;
    this->ssa_str = STRING(ssa);
    this->ssa = ssa;
    this->setWindowTitle("SSA " + STRING(ssa) + " Expert");
    this->group = "SRC03-RF-SSA" + STRING(ssa);

    QString substitutions = "";
    foreach (QELabel* w, this->ui->tabWidget->findChildren<QELabel*>()) {
        substitutions = w->getVariableNameSubstitutionsProperty();
        substitutions += ",ssa=" + STRING(ssa);
        w->setVariableNameSubstitutionsProperty(substitutions);
    }

    foreach (QEPushButton* w, this->ui->tabWidget->findChildren<QEPushButton*>()) {
        substitutions = w->getVariableNameSubstitutionsProperty();
        substitutions += ",ssa=" + STRING(ssa);
        w->setVariableNameSubstitutionsProperty(substitutions);
    }

    foreach (QESimpleShape* w, this->ui->tabWidget->findChildren<QESimpleShape*>()) {
        substitutions = w->getVariableNameSubstitutionsProperty();
        substitutions += ",ssa=" + STRING(ssa);
        w->setVariableNameSubstitutionsProperty(substitutions);
    }

    foreach (QELineEdit* w, this->ui->tabWidget->findChildren<QELineEdit*>()) {
        substitutions = w->getVariableNameSubstitutionsProperty();
        substitutions += ",ssa=" + STRING(ssa);
        w->setVariableNameSubstitutionsProperty(substitutions);
    }

    pvFWDPower = new QEpicsPV(this->group + "-DIS00:getUpperForwardPower");
    pvRFLPower = new QEpicsPV(this->group + "-DIS00:getUpperReflectedPower");
    QObject::connect(pvFWDPower, SIGNAL(valueChanged(QVariant)), this, SLOT(preDriverPower_Changed()));
    QObject::connect(pvRFLPower, SIGNAL(valueChanged(QVariant)), this, SLOT(preDriverPower_Changed()));
}

FormAmplifierExpert::~FormAmplifierExpert()
{
    delete ui;
}

void FormAmplifierExpert::preDriverPower_Changed()
{
    //set the value for Dial Forwarded Amplifier Power
    QwtDialSimpleNeedle* needle = new QwtDialSimpleNeedle(QwtDialSimpleNeedle::Arrow);
    ui->dialForwardPower->setNeedle(needle);
    ui->dialForwardPower->setValue(pvFWDPower->get().toDouble());
    ui->lblForwardPower->setText( QString::asprintf("%.3f", pvFWDPower->get().toDouble()) );

    //set the value for Dial Reflected Amplifier Power
    QwtDialSimpleNeedle* needle2 = new QwtDialSimpleNeedle(QwtDialSimpleNeedle::Arrow);
    ui->dialReflectedPower->setNeedle(needle2);
    ui->dialReflectedPower->setValue(pvRFLPower->get().toDouble());
    ui->lblReflectedPower->setText( QString::asprintf("%.3f", pvRFLPower->get().toDouble()) );
}

void FormAmplifierExpert::on_btnReset_clicked()
{
    QString pvName;

    for(int dis = 0; dis <= 10; dis++)
    {
        pvName = this->group + QString::asprintf("-DIS%02d:resetInterlocks", dis);
        qDebug() << pvName;
        Client::writePV(pvName, 1);
    }
}

void FormAmplifierExpert::on_btnSetPAVoltage_clicked()
{
    //SRC03-RF-SSA$(ssa)-REC00:setDcVoltage
    QString pv = "SRC03-RF-SSA"+this->ssa_str+"-REC00:setDcVoltage";
    Client::writePV(pv, ui->lineEditPAVoltage->text().toDouble());
}

void FormAmplifierExpert::on_btnSetAmpVoltage_clicked()
{
    QString pv;
    double value;
    bool ok;

    value = ui->lineEditAmpVoltage->text().toDouble(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Error", "Invalid value", QMessageBox::Ok);
        return;
    }

    if (value > 50) {
        QMessageBox::warning(this, "Error", "Maximum voltage entered", QMessageBox::Ok);
        return;
    }

    for (int i = 1; i <= 5; i++) {
        pv = QString::asprintf("SRC03-RF-SSA%d-REC0%d:setDcVoltage", this->ssa, i);
        Client::writePV(pv, value);
    }
}
