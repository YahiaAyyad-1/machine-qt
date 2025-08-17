#include "FormCorrectorPlotter.h"
#include "ui_FormCorrectorPlotter.h"

FormCorrectorPlotter::FormCorrectorPlotter(QString group, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormCorrectorPlotter)
{
    ui->setupUi(this);
    this->group = group;
    this->setWindowTitle(this->group + " Plotter");
    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));

    this->ui->pltBusVoltage->setVariableName1Property(this->group + ":getVbus");
    this->ui->pltVoltage->setVariableName1Property(this->group + ":getVmon");
    this->ui->pltILoad->setVariableName1Property(this->group + ":getIload");
    this->ui->lblBusVoltage->setVariableNameProperty(this->group + ":getVbus");
    this->ui->lblVoltage->setVariableNameProperty(this->group + ":getVmon");
    this->ui->lblILoad->setVariableNameProperty(this->group + ":getIload");
}

FormCorrectorPlotter::~FormCorrectorPlotter()
{
    delete ui;
}
