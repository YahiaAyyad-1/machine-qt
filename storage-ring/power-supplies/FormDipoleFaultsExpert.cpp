#include "FormDipoleFaultsExpert.h"
#include "ui_FormDipoleFaultsExpert.h"

FormDipoleFaultsExpert::FormDipoleFaultsExpert(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormDipoleFaultsExpert)
{
    ui->setupUi(this);
    CONNECT_CLOSE_BUTTON;
}

FormDipoleFaultsExpert::~FormDipoleFaultsExpert()
{
    delete ui;
}
