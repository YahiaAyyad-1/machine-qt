#include "FormDiagnostics.h"
#include "ui_FormDiagnostics.h"
#include <QCryptographicHash>
#include <qepicspv.h>
#include "client.h"
#include "../../general/FormPassword.h"
#include "qdebug.h"

FormDiagnostics::FormDiagnostics(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormDiagnostics)
{
    ui->setupUi(this);

    this->pvMotorDIFF = new QEpicsPV("SR-MO-MC1:SRC01-FS-STP-TRSY1.DIFF");
    this->pvMotorDMOV = new QEpicsPV("SR-MO-MC1:SRC01-FS-STP-TRSY1.DMOV");
    this->pvMotorRBV  = new QEpicsPV("SR-MO-MC1:SRC01-FS-STP-TRSY1.RBV");
    this->pvEnergy    = new QEpicsPV("SR-DI:getBeamEnergy");
    this->isIn_SRC10  = new QEpicsPV("SRC10-DI-FS1:isIn");
    this->isIn_SRC06  = new QEpicsPV("SRC06-DI-FS1:isIn");
    this->shutter_fault = new QEpicsPV("SRC14-VA-SHUTTER:isFault");
    this->shutter_closed = new QEpicsPV("SRC14-VA-SHUTTER:isClosed");
    this->shutter_opened = new QEpicsPV("SRC14-VA-SHUTTER:isOpen");
    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
    QObject::connect(this->pvMotorDIFF, SIGNAL(valueChanged(QVariant)), this, SLOT(motorData_Changed()));
    QObject::connect(this->pvMotorDMOV, SIGNAL(valueChanged(QVariant)), this, SLOT(motorData_Changed()));
    QObject::connect(this->pvMotorRBV, SIGNAL(valueChanged(QVariant)), this, SLOT(motorData_Changed()));
    QObject::connect(this->pvEnergy, SIGNAL(valueChanged(QVariant)), this, SLOT(beamEnergy_Changed()));
    QObject::connect(shutter_fault, SIGNAL(valueChanged(QVariant)), this, SLOT(shutter_state()));
    QObject::connect(shutter_closed, SIGNAL(valueChanged(QVariant)), this, SLOT(shutter_state()));
    QObject::connect(shutter_opened, SIGNAL(valueChanged(QVariant)), this, SLOT(shutter_state()));

    FIX_SIZE;
    this->eff = NULL;
    this->filling   = NULL;
    this->libraMain = NULL;
    this->srm       = NULL;
    this->shaker    = NULL;
    this->scraper   = NULL;
    this->dcct      = NULL;
    this->bpm       = NULL;
    this->fast      = NULL;
    this->bpmConfig = NULL;
    this->blm       = NULL;
    this->pinhole   = NULL;
    this->beats_pico = NULL;
    this->van = NULL;
    this->spark = NULL;
    this->cams = NULL;
    this->fct = NULL;
}

FormDiagnostics::~FormDiagnostics()
{
    delete ui;
}

void FormDiagnostics::on_btnMoveOut_clicked()
{
    // Client::writePV("SRC02-DI-FS1:setOut", 1);
    Client::writePV("SR-MO-MC1:SRC01-FS-STP-TRSY1.VAL", 100000);
    Client::writePV("SRC06-DI-FS1:setOut", 1);
    Client::writePV("SRC10-DI-FS1:setOut", 1);
}

void FormDiagnostics::beamEnergy_Changed()
{
    double loss = ( 88.5 * pow(this->pvEnergy->get().toFloat(), 4.0) ) / 5.95643;
    this->ui->lblLoss->setText(QString::number(loss));
}

void FormDiagnostics::motorData_Changed()
{
    float position = this->pvMotorRBV->get().toFloat();
    float error    = this->pvMotorDIFF->get().toFloat();
    int   status   = this->pvMotorDMOV->get().toInt();

    if((position + error) == 28000 && status == 1)
        this->ui->ledFT->setValue(1);
    else
        this->ui->ledFT->setValue(0);

    if((position + error) == 5500 && status == 1)
        this->ui->ledIN->setValue(1);
    else
        this->ui->ledIN->setValue(0);
}

void FormDiagnostics::on_pushButton_clicked()
{
    OPEN_UI(this->filling, FormFilling, this);
}

void FormDiagnostics::on_pushButton_3_clicked()
{
    OPEN_UI(this->srm, FormSRM, this);
}

void FormDiagnostics::on_pushButton_4_clicked()
{
    OPEN_UI(this->shaker, FormSRShaker, this);
}

void FormDiagnostics::on_pushButton_6_clicked()
{
    OPEN_UI(this->scraper, FormScraper, this);
}

void FormDiagnostics::on_pushButton_5_clicked()
{
    OPEN_UI(this->dcct, FormDCCTExpert, "SRC01-DI-DCCT1", this);
}

void FormDiagnostics::on_btnSchematic_clicked()
{
    OPEN_UI(this->bpm, FormBPMSchematic, this);
}

void FormDiagnostics::on_btnFast_clicked()
{
    OPEN_UI(this->fast, FormFastInterlock, this);
}

void FormDiagnostics::on_btnConfig_clicked()
{
    OPEN_UI(this->bpmConfig, FormBpmConfig, this);
}

void FormDiagnostics::on_SRC10SetIn_clicked()
{
    if (this->isIn_SRC10->get().toBool())
        return;

    QString goldenHash = "4af26a82c1521ca436bb994b079db63edacb4bf750b4db3c353b6287d683aafb";
    FormPassword * authObj = new FormPassword(goldenHash, this);
    QObject::connect(authObj, SIGNAL(authenticated()), this, SLOT(SRC10SetIn()));

    if (!FormPassword::dialogOpen) {
        authObj->show();
        FormPassword::dialogOpen = true;
    }
}

void FormDiagnostics::SRC10SetIn()
{
    Client::writePV("SRC10-DI-FS1:setIn", "1");
}

void FormDiagnostics::on_SRC06SetIn_clicked()
{
    if (this->isIn_SRC06->get().toBool())
        return;

    QString goldenHash = "4af26a82c1521ca436bb994b079db63edacb4bf750b4db3c353b6287d683aafb";
    FormPassword * authObj = new FormPassword(goldenHash, this);
    QObject::connect(authObj, SIGNAL(authenticated()), this, SLOT(SRC06SetIn()));

    if (!FormPassword::dialogOpen) {
        authObj->show();
        FormPassword::dialogOpen = true;
    }
}

void FormDiagnostics::SRC06SetIn()
{
    Client::writePV("SRC06-DI-FS1:setIn", "1");
}

void FormDiagnostics::on_btnBLMPlots_clicked()
{
    OPEN_UI(this->blm, FormBLMChannels, this);
}

void FormDiagnostics::shutter_state()
{
    int get_shutter_is_closed = shutter_closed->get().toInt();
    int get_shutter_is_open = shutter_opened->get().toInt();
    int get_shutter_is_fault = shutter_fault->get().toInt();

    if (get_shutter_is_fault == 1)
    {
        ui->shutter_state->setValue(0);
    }
    else if (get_shutter_is_closed == 1)
    {
        ui->shutter_state->setValue(1);
    }
    else if (get_shutter_is_open == 1)
    {
        ui->shutter_state->setValue(2);
    }
    else {

    }
}

void FormDiagnostics::on_qepushbutton_20_clicked()
{
    QMessageBox::information(this, "Information", "Auto ROI is applied");
}

void FormDiagnostics::on_btnGUI_clicked()
{
    QFile::copy(":/scripts/run-ad-cam", "/tmp/run-ad-cam");
    QProcess* p = new QProcess(this);
    p->start("bash /tmp/run-ad-cam SRC06-DI-IAXD CAM");

    QFile::copy(":/scripts/run-ad-viewer", "/tmp/run-ad-viewer");
    p = new QProcess(this);
    p->start("bash /tmp/run-ad-viewer SRC06-DI-IAXD CAM");
}

void FormDiagnostics::on_btnPinhole_clicked()
{
    OPEN_UI(this->pinhole, PinholeWindow, this);
}

void FormDiagnostics::on_btnXbpm_clicked()
{
    OPEN_UI(this->beats_pico, FormBeatsPicoammeter, this);
}

void FormDiagnostics::on_btnLibera_clicked()
{
    OPEN_UI(this->libraMain, FormSRLiberaMain, this);
}

void FormDiagnostics::on_btnEff_clicked()
{
    OPEN_UI(this->eff, FormInjectionEfficiency, this);
}

void FormDiagnostics::on_btnVAN_clicked()
{
    OPEN_UI(this->van, VibrationAnalyzerWindow, this);
}

void FormDiagnostics::on_qepushbutton_9_clicked()
{
    OPEN_UI(this->spark, LiberaSparkWindow, this);
}

void FormDiagnostics::on_btnCameras_clicked()
{
    OPEN_UI(this->cams, CamerasWindow, this);
}

void FormDiagnostics::on_btnScopesFCT_clicked()
{
    OPEN_UI(this->fct, ScopesWindow, "Storage-Ring FCTs", {"SR-DI-OSC1:wave:CH1", "SR-DI-OSC1:wave:CH2", "SR-DI-OSC1:wave:CH3"}, {"SR-FCT", "TL2-FCT1", "TL2-FCT2"}, this);
}
