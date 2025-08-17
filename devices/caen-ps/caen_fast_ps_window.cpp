#include "caen_fast_ps_window.h"
#include "ui_caen_fast_ps_window.h"

CaenFastPSWindow::CaenFastPSWindow(QString group, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CaenFastPSWindow)
{
    ui->setupUi(this);

    this->group = group;
    SET_GROUP(QELabel);
    SET_GROUP(QELineEdit);
    SET_GROUP(QEPushButton);
    SET_GROUP(QEBitStatus);

    CONNECT_CLOSE_BUTTON;
    this->setWindowTitle(this->group);
}

CaenFastPSWindow::~CaenFastPSWindow()
{
    delete ui;
}
