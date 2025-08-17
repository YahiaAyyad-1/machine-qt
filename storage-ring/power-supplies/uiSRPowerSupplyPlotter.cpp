#include "uiSRPowerSupplyPlotter.h"
#include "ui_uiSRPowerSupplyPlotter.h"

uiSRPowerSupplyPlotter::uiSRPowerSupplyPlotter(QString group, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::uiSRPowerSupplyPlotter)
{
    ui->setupUi(this);

    ui->pltILoad->setVariableName1Property(group + ":getIload");
    ui->pltIEarth->setVariableName1Property(group + ":getIearth");
    ui->pltVoltage->setVariableName1Property(group + ":getVmon");
    ui->lblILoad->setVariableNameProperty(group + ":getIload");
    ui->lblIEarth->setVariableNameProperty(group + ":getIearth");
    ui->lblVoltage->setVariableNameProperty(group + ":getVmon");

    this->setWindowTitle(group + " - Plotter");
    // this->plotData = new double[this->ui->pltILoad->getTimeSpan()];

    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
}

uiSRPowerSupplyPlotter::~uiSRPowerSupplyPlotter()
{
    delete ui;
}

void uiSRPowerSupplyPlotter::on_pltILoad_mouseMove(const QPointF &posn)
{
    // this->ui->label->setText("X = " + QString::number(posn.x()) + " | Y = " + QString::number(posn.y()));

    int x = (int) fabs(posn.x());
    if(x < this->plotData.size())
        this->ui->pltILoad->setToolTip("Value = " + QString::number(this->plotData[x]));
    else
        this->ui->pltILoad->setToolTip("Value = " + QString::number(this->plotData[this->plotData.size() - 1]));
}

void uiSRPowerSupplyPlotter::on_pltILoad_dbValueChanged(double out)
{
    if(this->plotData.size() == this->ui->pltILoad->getTimeSpan())
        this->plotData.erase(this->plotData.begin());
    this->plotData.insert(0, out);
}
