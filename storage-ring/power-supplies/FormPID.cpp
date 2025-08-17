#include "FormPID.h"
#include "ui_FormPID.h"

FormPID::FormPID(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormPID)
{
    ui->setupUi(this);
    connect(ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
    this->dcct = NULL;
}

FormPID::~FormPID()
{
    delete ui;
}

void FormPID::on_btnDMM_clicked()
{
    OPEN_UI(this->dcct, FormDCCTExpert, "TEST-DCCT", this);
}
