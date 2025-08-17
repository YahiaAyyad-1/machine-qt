#include "uiSR_RF.h"
#include "ui_uiSR_RF.h"

uiSR_RF::uiSR_RF(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::uiSR_RF)
{
    ui->setupUi(this);
    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
    QObject::connect(ui->btnExpert1, SIGNAL(clicked(bool)), this, SLOT(detailsButtonsClicked()));
    QObject::connect(ui->btnExpert2, SIGNAL(clicked(bool)), this, SLOT(detailsButtonsClicked()));
    QObject::connect(ui->btnExpert3, SIGNAL(clicked(bool)), this, SLOT(detailsButtonsClicked()));
    QObject::connect(ui->btnExpert4, SIGNAL(clicked(bool)), this, SLOT(detailsButtonsClicked()));
    QObject::connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(plunger_gui_selector(int)));
    this->frontEnd = NULL;
    this->cooling = NULL;
    this->diag = NULL;
    this->PlungerMotors = NULL;
}

uiSR_RF::~uiSR_RF()
{
    delete ui;
}

void uiSR_RF::on_btnCoolingRacks_clicked()
{
    CoolingRacks=new uiSR_RFCoolingRacks();
    CoolingRacks->show();
}

void uiSR_RF::on_btnMO_clicked()
{
    this->mo = new FormMasterOscillator;
    this->mo->show();
}

void uiSR_RF::on_btnInterlocks_clicked()
{
    this->lle = new FormLLEInterlocks;
    showUI(this->lle);
}

void uiSR_RF::on_btnAmp_clicked()
{
    this->amp = new FormTMBFAmplifier;
    showUI(this->amp);
}

void uiSR_RF::detailsButtonsClicked()
{
    QPushButton* button = (QPushButton*) sender();
    QString name = button->objectName();
    int index = name[name.length() - 1].toLatin1() - 0x30;
    QString title = "SSA " + STRING(index) + " Expert";
    foreach (QWidget* w, QApplication::topLevelWidgets()) {
        if(w->windowTitle() == title)
        {
            showUI(w);
            return;
        }
    }

    this->expert = new FormAmplifierExpert(index, this);
    showUI(this->expert);
}

void uiSR_RF::on_btnFrontEnd_clicked()
{
    OPEN_UI(this->frontEnd, FormFrontEndBBB, this);
}

void uiSR_RF::on_qepushbutton_3_clicked()
{
    QProcess* p = new QProcess;
    p->start("gnome-terminal --geometry 100x30 -x PS_Ramping.py");
}

void uiSR_RF::on_btnCooling_clicked()
{
    OPEN_UI(this->cooling, FormRFCooling, this);
}

void uiSR_RF::on_pushButton_clicked()
{
    OPEN_UI(this->diag, FormRFDiagnostics, this);
}

void uiSR_RF::plunger_gui_selector(int index)
{

    if(index==1)
    {
        OPEN_UI(this->PlungerMotors, FormPlungerMotors, this);
        ui->comboBox->setCurrentIndex(0);
    }
    else if (index==2)
    {
        this->galil = new FormGalilController("SRC03-MO-MC1", "SRC03-STP-CAV1,SRC03-STP-CAV2,SRC03-STP-CAV3,SRC03-STP-CAV4,,,,", ",,,,,,,");
        showUI(galil);
        ui->comboBox->setCurrentIndex(0);
    }
}

