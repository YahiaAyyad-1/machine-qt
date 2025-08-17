#include "FormFaultsExperts.h"
#include "ui_FormFaultsExperts.h"

FormFaultsExperts::FormFaultsExperts(QString group, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormFaultsExperts)
{
    ui->setupUi(this);

    CONNECT_CLOSE_BUTTON;

    this->group = group;
    SET_GROUP(QESimpleShape);
    SET_GROUP(QEPushButton);
    SET_GROUP(QELabel);

//    QList<QESimpleShape*> leds = this->findChildren<QESimpleShape*>();
//    for(QESimpleShape* led : leds)
//    {
//        led->setVariableNameSubstitutionsProperty("group=" + group);
//    }

//    QList<QELabel*> labels = this->findChildren<QELabel*>();
//    for(QELabel* label : labels)
//    {
//        label->setVariableNameSubstitutionsProperty("group=" + group);
//    }

//    QList<QEPushButton*> buttons = this->findChildren<QEPushButton*>();
//    for(QEPushButton* btn : buttons)
//    {
//        btn->setVariableNameSubstitutionsProperty("group=" + group);
//    }

    this->setWindowTitle(group + " - Faults");
}

FormFaultsExperts::~FormFaultsExperts()
{
    delete ui;
}
