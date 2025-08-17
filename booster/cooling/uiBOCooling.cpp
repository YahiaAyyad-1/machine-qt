#include "uiBOCooling.h"
#include "ui_uiBOCooling.h"

#include "client.h"

uiBOCooling::uiBOCooling(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::uiBOCooling)
{
    ui->setupUi(this);
    QObject::connect(ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
}

uiBOCooling::~uiBOCooling()
{
    delete ui;
}

void uiBOCooling::on_btnReset_clicked()
{
    Client::writePV("BO-CO-SB:reset", 1);
}
