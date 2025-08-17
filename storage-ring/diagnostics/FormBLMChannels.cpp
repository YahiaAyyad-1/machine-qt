#include "FormBLMChannels.h"
#include "ui_FormBLMChannels.h"

FormBLMChannels::FormBLMChannels(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormBLMChannels)
{
    ui->setupUi(this);
    QObject::connect(ui->btnClose, SIGNAL(clicked()), this, SLOT(close()));
}

FormBLMChannels::~FormBLMChannels()
{
    delete ui;
}
