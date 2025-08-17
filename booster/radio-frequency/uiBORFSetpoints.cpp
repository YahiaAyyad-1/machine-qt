#include "uiBORFSetpoints.h"
#include "ui_uiBORFSetpoints.h"

#include "client.h"

uiBORFSetpoints::uiBORFSetpoints(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::uiBORFSetpoints)
{
    ui->setupUi(this);
    QObject::connect(ui->btnClose_, SIGNAL(clicked(bool)), this, SLOT(close()));
}

uiBORFSetpoints::~uiBORFSetpoints()
{
    delete ui;
}

void uiBORFSetpoints::on_btnBlowerOFF_clicked()
{
    Client::writePV("BOC06-RF-CAV:disableAirBlower", 1);
}

void uiBORFSetpoints::on_btnBlowerON_clicked()
{
    Client::writePV("BOC06-RF-CAV:enableAirBlower", 1);
}
