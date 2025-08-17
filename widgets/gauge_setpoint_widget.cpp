#include "gauge_setpoint_widget.h"
#include "ui_gauge_setpoint_widget.h"

GaugeSetpointWidget::GaugeSetpointWidget(QString imgPrefix, int gc, int channel, bool isRedundant, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GaugeSetpointWidget)
{
    ui->setupUi(this);

    QString setpointPrefix = QString("gc=%1,sp=%2").arg(gc).arg(channel);
    ui->lblTitle->setText(imgPrefix);
    ui->lblGauge->setVariableNameSubstitutionsProperty("prefix=" + imgPrefix);
    ui->lblSetpointOFF->setVariableNameSubstitutionsProperty(setpointPrefix);
    ui->txtSetpointOFF->setVariableNameSubstitutionsProperty(setpointPrefix);
    ui->lblSetpointON->setVariableNameSubstitutionsProperty(setpointPrefix);
    ui->txtSetpointON->setVariableNameSubstitutionsProperty(setpointPrefix);
    ui->lblRelay1State->setVariableNameSubstitutionsProperty(setpointPrefix);
    if(!isRedundant) {
        ui->lblRelay2State->setVariableNameProperty("");
        ui->lblRelay2State->setText("");
        ui->lblRelay2State->setFrameShape(QLabel::NoFrame);
    }
    else {
        ui->lblRelay2State->setVariableNameSubstitutionsProperty(setpointPrefix);
    }
}

GaugeSetpointWidget::~GaugeSetpointWidget()
{
    delete ui;
}
