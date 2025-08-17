#include "FormMotors.h"
#include "ui_FormMotors.h"

FormMotors::FormMotors(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormMotors)
{
    ui->setupUi(this);

    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
}

FormMotors::~FormMotors()
{
    delete ui;
}
