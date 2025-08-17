#include "caen_easy_ps_window.h"
#include "ui_caen_easy_ps_window.h"

CaenEasyPSWindow::CaenEasyPSWindow(QString group, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CaenEasyPSWindow)
{
    ui->setupUi(this);

    this->group = group;
    SET_GROUP(QELabel);
    SET_GROUP(QELineEdit);
    SET_GROUP(QEPushButton);
    SET_GROUP(QEComboBox);
    SET_GROUP(QESimpleShape);

    CONNECT_CLOSE_BUTTON;
    this->setWindowTitle(this->group);
}

CaenEasyPSWindow::~CaenEasyPSWindow()
{
    delete ui;
}
