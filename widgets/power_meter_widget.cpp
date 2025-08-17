#include "power_meter_widget.h"
#include "ui_power_meter_widget.h"

power_meter_widget::power_meter_widget(QString devNum, QString title, QString type, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::power_meter_widget)
{
    ui->setupUi(this);

    this->ui->lblTitle->setText(title);

    QList<QGroupBox* >groupBoxes = this->ui->parentWidget->findChildren<QGroupBox*>();
    for (QGroupBox *groupBox : groupBoxes)
    {
        QList<QELabel*> labels = groupBox->findChildren<QELabel*>();
        for (QELabel *label: labels)
        {
            label->setVariableNameSubstitutionsProperty("num=" + devNum);
        }
    }

    this->ui->ledPowerOn->setVariableNameSubstitutionsProperty("type=" + type);
    this->ui->ledEmergency->setVariableNameSubstitutionsProperty("type=" + type);
}

power_meter_widget::~power_meter_widget()
{
    delete ui;
}
