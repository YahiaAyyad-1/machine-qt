#include "FormLLEInterlocks.h"
#include "ui_FormLLEInterlocks.h"

FormLLEInterlocks::FormLLEInterlocks(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormLLEInterlocks)
{
    ui->setupUi(this);

    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
}

FormLLEInterlocks::~FormLLEInterlocks()
{
    delete ui;
}
