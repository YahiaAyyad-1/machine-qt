#include "formpicoposition.h"
#include "ui_formpicoposition.h"

FormPicoPosition::FormPicoPosition(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormPicoPosition)
{
    ui->setupUi(this);
}

FormPicoPosition::~FormPicoPosition()
{
    delete ui;
}
