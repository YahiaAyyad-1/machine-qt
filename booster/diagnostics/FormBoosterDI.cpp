#include "FormBoosterDI.h"
#include "ui_FormBoosterDI.h"

#include "client.h"

FormBoosterDI::FormBoosterDI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormBoosterDI)
{
    ui->setupUi(this);
    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));

    dcct = NULL;
    scopes = NULL;
}

FormBoosterDI::~FormBoosterDI()
{
    delete ui;
}

void FormBoosterDI::on_btnMoveScreens_clicked()
{
    Client::writePV("BO-DI-FOMS:setOut", 1);
    Client::writePV("TL1-DI-FOM1:setIn", 1);
}

void FormBoosterDI::on_btnOpenSRM_clicked()
{
    this->srm = new FormBoosterSRM;
    this->srm->show();
}

void FormBoosterDI::on_btnOpenDCCT_clicked() { if(!dcct) dcct = new FormDCCTExpert("BO-DI-DCCT1", this); showUI(dcct); dcct = NULL; }

void FormBoosterDI::on_pushButton_15_clicked()
{
    this->shaker = new FormShaker;
    this->shaker->show();
}

void FormBoosterDI::on_pushButton_16_clicked()
{
    this->afg = new FormAFG;
    this->afg->show();
}

void FormBoosterDI::on_pushButton_14_clicked()
{
    this->libera = new FormLiberaMain;
    this->libera->show();
}

void FormBoosterDI::on_btnScopes_clicked()
{
    OPEN_UI(this->scopes,
            ScopesWindow,
            "Booster FCTs",
            {"BO-DI-OSC:wave:CH1", "BO-DI-OSC:wave:CH2", "BO-DI-OSC:wave:CH3", "BO-DI-OSC:wave:CH4"},
            {"Booster Injection Septum", "Booster Injection Kicker", "TL1-FCT", "Booster FCT"},
            this);
}
