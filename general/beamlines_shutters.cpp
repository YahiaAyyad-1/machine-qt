#include "beamlines_shutters.h"
#include "ui_beamlines_shutters.h"

beamlines_shutters::beamlines_shutters(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::beamlines_shutters)
{
    ui->setupUi(this);
    CONNECT_CLOSE_BUTTON;
}

beamlines_shutters::~beamlines_shutters()
{
    delete ui;
}
