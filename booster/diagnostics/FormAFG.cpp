#include "FormAFG.h"
#include "ui_FormAFG.h"

FormAFG::FormAFG(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormAFG)
{
    ui->setupUi(this);
    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
}

FormAFG::~FormAFG()
{
    delete ui;
}
