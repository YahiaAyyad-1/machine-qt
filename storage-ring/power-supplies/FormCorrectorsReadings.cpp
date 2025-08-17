#include "FormCorrectorsReadings.h"
#include "ui_FormCorrectorsReadings.h"

FormCorrectorsReadings::FormCorrectorsReadings(QString group, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormCorrectorsReadings)
{
    ui->setupUi(this);
    this->group = group;
    QObject::connect(ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
    SET_GROUP(QELabel);

    this->setWindowTitle(this->group + " - Readings");
}

FormCorrectorsReadings::~FormCorrectorsReadings()
{
    delete ui;
}
