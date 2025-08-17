#include "FormGauges.h"
#include "ui_FormGauges.h"
#include "client.h"

FormGauges::FormGauges(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormGauges)
{
    ui->setupUi(this);
    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
}

FormGauges::~FormGauges()
{
    delete ui;
}

void FormGauges::on_btnReset_clicked()
{
    Client::writePV("SR-VA-IMG:reset", 1);
    Client::writePV("SR-VA-IP:resetInterlocks", 1);
}
