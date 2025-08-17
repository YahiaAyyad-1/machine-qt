#include "caen_ps_widget.h"
#include "ui_caen_ps_widget.h"

CaenPowerSupplyWidget::CaenPowerSupplyWidget(QString group, bool isFastPS, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CaenPowerSupplyWidget)
{
    ui->setupUi(this);

    this->group = group;
    this->isFastPS = isFastPS;
    if(this->isFastPS) {
        ui->lblCurrent->setVariableNameProperty("$(group):OutputCurrent");
        ui->txtCurrent->setVariableNameProperty("$(group):Current");
        ui->ledStatus->setVariableNameProperty("$(group):Enable");
        ui->ledInterlock->setVariableNameProperty("$(group):StatusLSB.B1");
    }
    SET_GROUP(QELabel);
    SET_GROUP(QENumericEdit);
    SET_GROUP(QESimpleShape);
    SET_GROUP(QEPushButton);

    this->psDetails = NULL;
    this->fastPSDetails = NULL;
}

CaenPowerSupplyWidget::~CaenPowerSupplyWidget()
{
    delete ui;
}

void CaenPowerSupplyWidget::on_btnDetails_clicked()
{
    if(this->isFastPS) {
        OPEN_UI(this->fastPSDetails, CaenFastPSWindow, this->group);
    }
    else {
        OPEN_UI(this->psDetails, CaenEasyPSWindow, this->group);
    }
}
