#include "FormMainPower.h"
#include "ui_FormMainPower.h"

FormMainPower::FormMainPower(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormMainPower)
{
    ui->setupUi(this);
    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));

    this->detailsWindow = NULL;
}

FormMainPower::~FormMainPower()
{
    delete ui;
}

void FormMainPower::on_btnDetails_clicked()
{
    OPEN_UI(this->detailsWindow, FormMainPowerDetails, this);
}
