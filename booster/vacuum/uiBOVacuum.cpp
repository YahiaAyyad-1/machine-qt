#include "uiBOVacuum.h"
#include "ui_uiBOVacuum.h"

#include "client.h"

uiBOVacuum::uiBOVacuum(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::uiBOVacuum)
{
    ui->setupUi(this);
    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));

    this->valves = NULL;
}

uiBOVacuum::~uiBOVacuum()
{
    delete ui;
}

void uiBOVacuum::on_btnChannel1OFF_clicked() { Client::writePV("BO-VA-IPC1-CH1:enable", 0); }

void uiBOVacuum::on_btnChannel1ON_clicked()  { Client::writePV("BO-VA-IPC1-CH1:enable", 1); }

void uiBOVacuum::on_btnChannel2OFF_clicked() { Client::writePV("BO-VA-IPC1-CH2:enable", 0); }

void uiBOVacuum::on_btnChannel2ON_clicked()  { Client::writePV("BO-VA-IPC1-CH2:enable", 1); }

void uiBOVacuum::on_pushButton_clicked()
{
    this->boosterGC = new uiBoosterVacuumGC;
    this->boosterGC->show();
}

void uiBOVacuum::on_btnOpenIPC_clicked()
{
    this->boosterIPC = new uiBoosterIPC;
    this->boosterIPC->show();
}

void uiBOVacuum::on_btnValves_clicked()
{
    OPEN_UI(valves, ValvesWindow, this);
}
