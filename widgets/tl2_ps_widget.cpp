#include "tl2_ps_widget.h"
#include "ui_tl2_ps_widget.h"

TL2PowerSupplyWidget::TL2PowerSupplyWidget(QString prefix, QString enableSuffix, QString rsdSuffix, QStringList coolingPVs, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TL2PowerSupplyWidget)
{
    ui->setupUi(this);

    this->prefix = prefix;

    ui->lblTitle->setText(prefix);
    ui->ledEnable->setVariableNameProperty(prefix + ":" + enableSuffix);
    ui->ledRSD->setVariableNameProperty(prefix + ":" + rsdSuffix);
    ui->lblVoltage->setVariableNameSubstitutionsProperty("prefix=" + prefix);
    ui->btnON->setVariableNameSubstitutionsProperty("prefix=" + prefix);
    ui->btnOFF->setVariableNameSubstitutionsProperty("prefix=" + prefix);
    ui->txtCurrent->setVariableNameSubstitutionsProperty("prefix=" + prefix);
    ui->lblCurrent->setVariableNameProperty(this->prefix + ":getCurrent");

    if (!coolingPVs.empty()) {
        temperaturePV = new QEpicsPV(coolingPVs[0]);
        flowPV = new QEpicsPV(coolingPVs[1]);

        QObject::connect(temperaturePV, &QEpicsPV::valueChanged, this, &TL2PowerSupplyWidget::onCoolingPVsChanged);
        QObject::connect(flowPV, &QEpicsPV::valueChanged, this, &TL2PowerSupplyWidget::onCoolingPVsChanged);
    }
    else {
        ui->ledCooling->setColour0Property(QColor(0xee, 0xee, 0xee));
        ui->ledCooling->setEdgeWidth(0);
    }

    if (this->prefix.startsWith("TL2-PS-Q"))
        ui->txtCurrent->setLeadingZeros(2);

    if (this->prefix.contains("BM1-Y") || this->prefix.contains("BM2-Y"))
        ui->ledEnable->setVariableNameProperty(this->prefix + ":isEnabled");

    this->pvCurrent = new QEpicsPV(prefix + ":getCurrent");
    this->pvVoltage = new QEpicsPV(prefix + ":getVoltage");
    QObject::connect(this->pvCurrent, &QEpicsPV::valueChanged, this, &TL2PowerSupplyWidget::onCurrentChanged);
    QObject::connect(this->pvVoltage, &QEpicsPV::valueChanged, this, &TL2PowerSupplyWidget::onVoltageChanged);
}

TL2PowerSupplyWidget::~TL2PowerSupplyWidget()
{
    delete ui;
}

void TL2PowerSupplyWidget::onCoolingPVsChanged()
{
    ui->ledCooling->setValue(this->temperaturePV->get().toInt() || this->flowPV->get().toInt());
}

void TL2PowerSupplyWidget::onCurrentChanged(QVariant value)
{
    double current;
    double setpoint;
    double currentThreshold;

    if(this->prefix.contains("BM1-X") || this->prefix.contains("BM2-X") || this->prefix.contains("THS")) {
        current = value.toDouble() * 3;
        ui->lblCurrent->setText(QString::number(current) + " A");
    }
    else {
        current = value.toDouble();
    }

    setpoint = ui->txtCurrent->getValue();
    if (this->prefix.startsWith("TL2-PS-Q"))
        currentThreshold = 0.05;
    else
        currentThreshold = 0.3;

    if (qAbs(current - setpoint) > currentThreshold)
        ui->lblCurrent->setStyleSheet(LABEL_ALARM_QSS);
    else
        ui->lblCurrent->setStyleSheet(LABEL_DEFAULT_QSS);
}

void TL2PowerSupplyWidget::onVoltageChanged(QVariant value)
{
    Q_UNUSED(value);
//    if (value.toDouble() < VOLTAGE_THRESHOLD)
//        ui->lblVoltage->setStyleSheet(LABEL_ALARM_QSS);
//    else
//        ui->lblVoltage->setStyleSheet(LABEL_DEFAULT_QSS);
}
