#include "uiBoosterIPC.h"
#include "ui_uiBoosterIPC.h"

#include "client.h"

uiBoosterIPC::uiBoosterIPC(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::uiBoosterIPC)
{
    ui->setupUi(this);
    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
}

uiBoosterIPC::~uiBoosterIPC()
{
    delete ui;
}

void uiBoosterIPC::on_btnEnableInterlocks_clicked()
{
    Client::writePV("BO-VA-IPC1:disableInterlocks", 0);
}

void uiBoosterIPC::on_btnDisableInterlocks_clicked()
{
    Client::writePV("BO-VA-IPC1:disableInterlocks", 1);
}
