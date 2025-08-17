#include "uiBoosterVacuumGC.h"
#include "ui_uiBoosterVacuumGC.h"

uiBoosterVacuumGC::uiBoosterVacuumGC(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::uiBoosterVacuumGC)
{
    ui->setupUi(this);

    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
}

uiBoosterVacuumGC::~uiBoosterVacuumGC()
{
    delete ui;
}
