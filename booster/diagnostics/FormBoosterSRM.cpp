#include "FormBoosterSRM.h"
#include "ui_FormBoosterSRM.h"

FormBoosterSRM::FormBoosterSRM(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormBoosterSRM)
{
    ui->setupUi(this);
    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
}

FormBoosterSRM::~FormBoosterSRM()
{
    delete ui;
}
