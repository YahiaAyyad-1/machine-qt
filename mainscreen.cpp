#include "mainscreen.h"
#include "ui_mainscreen.h"

MainScreen::MainScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScreen)
{
    ui->setupUi(this);
    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));

    this->srBmPs = new QEpicsPV("SR-CO-TCB01:getTC4");
    QObject::connect(this->srBmPs, SIGNAL(valueChanged(QVariant)), this, SLOT(srBmPsValueChanged()));
    // FIX_SIZE;

    this->microtron = NULL;
    this->microtronCoils = NULL;
    this->microtronAnalog = NULL;
    this->microtronMotors = NULL;
    this->tl1Power = NULL;
    this->tl1Vacuum = NULL;
    this->rfMain = NULL;
    this->cooling = NULL;
    this->boVacuum = NULL;
    this->boPS = NULL;
    this->boDI = NULL;
    this->tl2Cooling = NULL;
    this->tl2Diagnostics = NULL;
    this->tl2Power = NULL;
    this->tl2Vacuum = NULL;
    this->srPower = NULL;
    this->srVacuum = NULL;
    this->srRF = NULL;
    this->srCooling = NULL;
    this->srDiag = NULL;
    this->dcct = NULL;
    this->evg = NULL;
    this->evr0 = NULL;
    this->evr1 = NULL;
    this->mps = NULL;
    this->profiles = NULL;
    this->beamlines = NULL;
    this->blInterlocks = NULL;
    this->manager = NULL;
    this->monitors = NULL;
    this->injection = NULL;
    this->c09wiggler = NULL;
    this->c11Undulator = NULL;
    this->message = NULL;
    this->beamlinesShutters = NULL;
    this->shuttersSafety = NULL;
}

MainScreen::~MainScreen()
{
    delete ui;
}

void MainScreen::on_btnMIOperation_clicked() { if(!microtron) microtron = new uiMicrotron(this); showUI(microtron); }

void MainScreen::on_btnSRPS_clicked() { OPEN_UI(srPower, RingPowerSupplyWindow, this); }

void MainScreen::on_btnMicrotronAnalog_clicked() { if(!microtronAnalog) microtronAnalog = new uiMicrotronAnalog(this); showUI(microtronAnalog); }

void MainScreen::on_btnMicrotronPS_clicked() { OPEN_UI(this->microtronCoils, MicrotronCoilsWindow, this); }

void MainScreen::on_btnTL1Power_clicked() { if(!tl1Power) tl1Power = new TL1CorrectorsWindow(this); showUI(tl1Power); }

void MainScreen::on_btnTL1Vacuum_clicked() { if(!tl1Vacuum) tl1Vacuum = new uiTL1Vacuum(this); showUI(tl1Vacuum); }

void MainScreen::on_pushButton_9_clicked() { if(!rfMain) rfMain = new uiBORFMain(this); showUI(rfMain); }

void MainScreen::on_pushButton_12_clicked() { if(!cooling) cooling = new uiBOCooling(this); showUI(cooling); }

void MainScreen::on_pushButton_8_clicked() { if(!boVacuum) boVacuum = new uiBOVacuum(this); showUI(boVacuum); }

void MainScreen::on_btnTL2Cooling_clicked() { if(!tl2Cooling) tl2Cooling = new uiTL2Cooling(this); showUI(tl2Cooling); }

void MainScreen::on_btnTL2PowerSupplies_clicked() { if(!tl2Power) tl2Power = new uiTL2PowerSupply(this); showUI(tl2Power); }

void MainScreen::on_btnTL2Diagnostics_clicked() { if(!tl2Diagnostics) tl2Diagnostics = new uiTL2Diagnostics(this); showUI(tl2Diagnostics); }

void MainScreen::on_btnTL2Vacuum_clicked() { if(!tl2Vacuum) tl2Vacuum = new uiTL2Vacuum(this); showUI(tl2Vacuum); }

void MainScreen::on_btnEVG_clicked() { evg = new uiTSEventGenerator(this); showUI(evg); }

void MainScreen::on_btnEVR1_clicked() { OPEN_UI(this->evr0, EventReceiverWindow, 0, this); }

void MainScreen::on_btnEVR2_clicked() { OPEN_UI(this->evr1, EventReceiverWindow, 1, this); }

void MainScreen::on_btnSRVacuum_clicked() { OPEN_UI(this->srVacuum, RingVacuumWindow, this) }

void MainScreen::on_btnSRRF_clicked() { if(!srRF) srRF = new uiSR_RF(this); showUI(srRF); }

void MainScreen::on_pushButton_10_clicked() { if(!boPS) this->boPS = new FormBoosterPS(this); showUI(boPS); }

void MainScreen::on_pushButton_11_clicked() { if(!boDI) boDI = new FormBoosterDI(this); showUI(boDI); }

void MainScreen::on_btnSRCooling_clicked()  { OPEN_UI(this->srCooling, RingCoolingWindow, this); }

void MainScreen::on_btnSRDiagnostics_clicked() { if(!srDiag) this->srDiag = new FormDiagnostics(this); showUI(srDiag); }

void MainScreen::on_btnMicrotronMotors_clicked() { if(!microtronMotors) this->microtronMotors = new FormMotors(this); showUI(microtronMotors); }

void MainScreen::on_btnMPS_clicked() { if(!mps) this->mps = new FormMPS(this); showUI(mps); }

void MainScreen::on_btnDCCT_clicked() { OPEN_UI(this->dcct, FormDCCT); }

void MainScreen::on_btnProfiles_clicked() { if(!profiles) this->profiles = new FormProfiles(this); showUI(profiles); }

void MainScreen::on_btnManager_clicked() { if(!manager) this->manager = new FormMachineManager(this); showUI(manager); }

void MainScreen::on_btnD09W_clicked() { if(!c09wiggler) this->c09wiggler = new FormWigglerC09(this); showUI(c09wiggler); }

void MainScreen::on_btnD11U_clicked() { if(!c11Undulator) this->c11Undulator = new FormUndulatorC11(this); showUI(c11Undulator); }

void MainScreen::on_btnMonitors_clicked() { if(!monitors) this->monitors = new FormRadiationMonitors(this); showUI(monitors); }

void MainScreen::on_btnInjection_clicked()
{
    OPEN_UI(this->injection, FormInjection, this);
}

void MainScreen::on_btnBeamlines_clicked()
{
    if(!this->beamlines)
        this->beamlines = new FormBeamlines(this);
    showUI(this->beamlines);
}

void MainScreen::on_btnMessage_clicked()
{
    OPEN_UI(this->message, FormMessage, this);
}


void MainScreen::on_btnD10W_clicked()
{
    this->c10wiggler = new Form3pwiggler(this); showUI(c10wiggler);
}


void MainScreen::on_comMachineStatus_activated(int index)
{
    QMessageBox::StandardButton reply = QMessageBox::question(nullptr, "Confirmation", "The machine status will be changed, are you sure?", QMessageBox::Yes|QMessageBox::No);

    if (index == 0 && reply == QMessageBox::Yes){
        Client::writePV("Machine:Status",0);

    }
    else if (index == 1 && reply == QMessageBox::Yes) {
        Client::writePV("Machine:Status",1);

    }
    else if (index == 2 && reply == QMessageBox::Yes) {
        Client::writePV("Machine:Status",2);

    }
    else if (index == 3 && reply == QMessageBox::Yes) {
        Client::writePV("Machine:Status",3);

    }
    else if (index == 4 && reply == QMessageBox::Yes) {
        Client::writePV("Machine:Status",4);

    }
    else if (index == 5 && reply == QMessageBox::Yes) {
        Client::writePV("Machine:Status",5);

    }
    else if (index == 6 && reply == QMessageBox::Yes) {
        Client::writePV("Machine:Status",6);

    }
    else if (index == 7 && reply == QMessageBox::Yes) {
        Client::writePV("Machine:Status",7);

    }
    else if (index == 8 && reply == QMessageBox::Yes) {
        Client::writePV("Machine:Status",8);

    }
}

void MainScreen::on_btnBeamlinesShutters_clicked()
{
    this->beamlinesShutters = new FormBeamlinesStatus(this);
    showUI(beamlinesShutters);
}

void MainScreen::srBmPsValueChanged()
{
    double current_temp = this->srBmPs->get().toDouble();
    QDateTime dateTime = dateTime.currentDateTime();
    QString currentDateTime = dateTime.toString("yyyy-MM-dd HH:mm");

    if(current_temp>=25.0 && srBmPs_status==0)
    {
        QMessageBox infoMsg;
        infoMsg.setWindowTitle("WARNING! SR dipole cooling temperature");
        infoMsg.setText("WARNING! The SR dipole cooling temperature has exceeded 25°C \n Timestamp: " + currentDateTime + "\n Current temperature: " + QString::number(current_temp));
        infoMsg.setIcon(QMessageBox::Information);
        infoMsg.addButton(QMessageBox::Ok);
        srBmPs_status = 1;
        infoMsg.exec();
    }
    else if(current_temp<25.0 && srBmPs_status==1)
    {
        srBmPs_status = 0;
    }

}

void MainScreen::on_btnShuttersSafety_clicked()
{
    OPEN_UI(this->shuttersSafety, beamlines_shutters, this);
}
