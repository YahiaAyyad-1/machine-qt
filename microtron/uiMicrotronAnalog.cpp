#include "uiMicrotronAnalog.h"
#include "ui_uiMicrotronAnalog.h"

uiMicrotronAnalog::uiMicrotronAnalog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::uiMicrotronAnalog)
{
    ui->setupUi(this);
    QObject::connect(ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
}

uiMicrotronAnalog::~uiMicrotronAnalog()
{
    delete ui;
}
