#include "FormBeamlinesInterlocks.h"
#include "ui_FormBeamlinesInterlocks.h"

FormBeamlinesInterlocks::FormBeamlinesInterlocks(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormBeamlinesInterlocks)
{
    ui->setupUi(this);
    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
}

FormBeamlinesInterlocks::~FormBeamlinesInterlocks()
{
    delete ui;
}

void FormBeamlinesInterlocks::on_btnIRreset_clicked()
{
    Client::writePV("D02C01-CO-FLS1:reset",1);
    Client::writePV("D02C01-VA-ABS:reset",1);
    Client::writePV("D02-CO-THC:reset",1);
}

void FormBeamlinesInterlocks::on_btnXAFSreset_clicked()
{
    Client::writePV("FE08-VA-GC1:reset",1);
    Client::writePV("FE08-VA-GV1:reset",1);
    Client::writePV("FE08-VA-PHSH:reset",1);
    Client::writePV("FE08-CO-FLS:reset",1);
}

void FormBeamlinesInterlocks::on_btnMSreset_clicked()
{
    Client::writePV("I09FE-CO-FLS:resetInterlock",1);
    Client::writePV("I09FE-CO-THC:resetInterlock",1);
    Client::writePV("I09FE-VA:resetInterlock",1);
    Client::writePV("I09FE-VA-GV:resetInterlock",1);
}

void FormBeamlinesInterlocks::on_btnBEATSreset_clicked()
{
    Client::writePV("I10-VA:resetInterlock",1);
    Client::writePV("I10-CO:resetInterlock",1);
}


void FormBeamlinesInterlocks::on_btnHESEBreset_clicked()
{
    Client::writePV("I11FE-CO-THC:resetInterlock",1);
    Client::writePV("I11FE-CO-FLS:resetInterlock",1);
    Client::writePV("I11FE-VA-GC1:resetInterlock",1);
    Client::writePV("I11FE-VA-GV:resetInterlock",1);
}
