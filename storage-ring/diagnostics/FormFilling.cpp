#include "FormFilling.h"
#include "ui_FormFilling.h"

FormFilling::FormFilling(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormFilling)
{
    ui->setupUi(this);
    QObject::connect(this->ui->btn_close, SIGNAL(clicked()), this, SLOT(close()));
    this->setFixedSize(this->width(), this->height());
}

FormFilling::~FormFilling()
{
    delete ui;
}
