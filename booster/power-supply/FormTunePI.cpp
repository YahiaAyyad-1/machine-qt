#include "FormTunePI.h"
#include "ui_FormTunePI.h"

FormTunePI::FormTunePI(QString magnet, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormTunePI)
{
    ui->setupUi(this);
    this->magnet = magnet;
    this->setWindowTitle(this->magnet + " Tuning");

    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));

    this->ui->lblKi->setVariableNameProperty("BO-PS-" + this->magnet + ":getRegulationKi");
    this->ui->lblKP->setVariableNameProperty("BO-PS-" + this->magnet + ":getRegulationKp");
    this->ui->txtKI->setVariableNameProperty("BO-PS-" + this->magnet + ":setRegulationKi");
    this->ui->txtKP->setVariableNameProperty("BO-PS-" + this->magnet + ":setRegulationKp");
}

FormTunePI::~FormTunePI()
{
    delete ui;
}
