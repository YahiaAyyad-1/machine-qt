#include "FormPlungerMotors.h"
#include "ui_FormPlungerMotors.h"

FormPlungerMotors::FormPlungerMotors(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormPlungerMotors)
{
    ui->setupUi(this);
    CONNECT_CLOSE_BUTTON;
}

FormPlungerMotors::~FormPlungerMotors()
{
    delete ui;
}
