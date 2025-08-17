#include "event_receiver_window.h"
#include "ui_event_receiver_window.h"

EventReceiverWindow::EventReceiverWindow(int evr, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EventReceiverWindow)
{
    ui->setupUi(this);
    this->prefix = "GBL-TI-EVR" + QString::number(evr);
    setWindowTitle( QString(evr == 0 ? "Booster" : "Storage-Ring") + " Event Receiver");
    for(int i = 0; i < PULSERS_COUNT; i++) {
        ui->ltPulsers->insertWidget(ui->ltPulsers->count(), new PulserWidget(this->prefix + "-P" + QString::number(i), this));
    }

    for(int i = 0; i < 4; i++) {
        ui->ltDelayed->insertWidget(ui->ltDelayed->count(), new DelayedPulserWidget(this->prefix + "-PDP" + QString::number(i), this));
        ui->ltUniversal->insertWidget(ui->ltUniversal->count(), new UniversalOutputWidget(this->prefix + "-UNIV" + QString::number(i), this));
        ui->ltTTL->insertWidget(ui->ltUniversal->count(), new TTLOutputWidget(this->prefix + "-TTL" + QString::number(i), this));
    }

    for(int i = 0; i < 3; i++) {
        ui->ltPrescalers->insertWidget(ui->ltPrescalers->count(), new PrescalerWidget(this->prefix + "-PRE" + QString::number(i), this));
        ui->ltCML->insertWidget(ui->ltUniversal->count(), new CmlOutputWidget(this->prefix + "-CML" + QString::number(i), this));
    }

    ui->ledEnable->setVariableNameSubstitutionsProperty("prefix=" + this->prefix);
    ui->ledRXViolation->setVariableNameSubstitutionsProperty("prefix=" + this->prefix);
    ui->btnOFF->setVariableNameSubstitutionsProperty("prefix=" + this->prefix);
    ui->btnON->setVariableNameSubstitutionsProperty("prefix=" + this->prefix);
    ui->btnRXReset->setVariableNameSubstitutionsProperty("prefix=" + this->prefix);

    QObject::connect(ui->btnClose, SIGNAL(clicked()), this, SLOT(close()));
}

EventReceiverWindow::~EventReceiverWindow()
{
    delete ui;
}
