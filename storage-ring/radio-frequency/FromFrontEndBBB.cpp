#include "FromFrontEndBBB.h"
#include "ui_FromFrontEndBBB.h"

FormFrontEndBBB::FormFrontEndBBB(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormFrontEndBBB)
{
    ui->setupUi(this);

    FIX_SIZE;
    CONNECT_CLOSE_BUTTON;
}

FormFrontEndBBB::~FormFrontEndBBB()
{
    delete ui;
}
