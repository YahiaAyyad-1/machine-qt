#include "FormCorrectorTuning.h"
#include "ui_FormCorrectorTuning.h"

FormCorrectorTuning::FormCorrectorTuning(QString group, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormCorrectorTuning)
{
    ui->setupUi(this);
    this->group = group;
    this->setWindowTitle(this->group + " Tuning");
    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));

    this->ui->cbSetAddress->setVariableNameProperty(this->group + ":setParameterAddress");
    this->ui->txtData->setVariableNameProperty(this->group + ":setParameterData");
    this->ui->lblData->setVariableNameProperty(this->group + ":getParameterData");
}

FormCorrectorTuning::~FormCorrectorTuning()
{
    delete ui;
}
