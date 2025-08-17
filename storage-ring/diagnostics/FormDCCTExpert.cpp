#include "FormDCCTExpert.h"
#include "ui_FormDCCTExpert.h"

FormDCCTExpert::FormDCCTExpert(QString group, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormDCCTExpert)
{
    ui->setupUi(this);
    CONNECT_CLOSE_BUTTON;

    this->group = group;
    SET_GROUP(QELabel);
    SET_GROUP(QEComboBox);
    QString timing = "";
    ui->groupRange->setVisible(false);
    if(this->group.startsWith("SR"))
    {
        timing = "group=GBL-TI-EVR1-P3";
        this->setWindowTitle("Storage-Ring DCCT");
        ui->lblTemp->setVariableNameSubstitutionsProperty("group=SRC01-DI-DCCT");
        this->pvDcct = new QEpicsPV("SRC01-DI-DCCT1:getDcctCurrent");
        ui->groupRange->setVisible(true);
    }
    else if(this->group.startsWith("BO"))
    {
        timing = "group=GBL-TI-EVR0-PDP1";
        this->setWindowTitle("Booster DCCT Control");
        ui->lblTemp->setVisible(false);
        ui->labelX->setVisible(false);
        this->pvDcct = new QEpicsPV("BO-DI-DCCT1:getDcctCurrent");
    }
    else if(this->group.startsWith("TEST"))
    {
        timing = "group=GBL-TI-EVR1-P3";
        this->setWindowTitle("Test DMM");
        ui->lblTemp->setVariableNameSubstitutionsProperty("group=TEST-DCCT");
        this->pvDcct = new QEpicsPV("TEST-DCCT:getDcctCurrent");
    }

    ui->ledEnabled->setVariableNameSubstitutionsProperty(timing);
    ui->btnOFF->setVariableNameSubstitutionsProperty(timing);
    ui->btnON->setVariableNameSubstitutionsProperty(timing);
    ui->lblDelay->setVariableNameSubstitutionsProperty(timing);
    ui->lblWidth->setVariableNameSubstitutionsProperty(timing);
    ui->txtDelay->setVariableNameSubstitutionsProperty(timing);
    ui->txtWidth->setVariableNameSubstitutionsProperty(timing);

    chart = new QChart;
    series = new QSplineSeries;
    series->setName("DCCT");
    chart->legend()->show();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setRange(0, BUFFER_SIZE);
    chart->axes(Qt::Vertical).first()->setRange(200, 250);

    this->ui->dcctPlot->setChart(chart);
    this->ui->dcctPlot->setRenderHint(QPainter::Antialiasing);

    this->numPoints = 0;
    min = std::numeric_limits<double>::min();
    max = std::numeric_limits<double>::max();
    margin = 0;

    this->timer = new QTimer;
    this->timer->setInterval(1000);
    this->timer->start();
    QObject::connect(this->timer, SIGNAL(timeout()), this, SLOT(onUpdateDcctPlot()));
}

FormDCCTExpert::~FormDCCTExpert()
{
    delete ui;
}

void FormDCCTExpert::on_cbSource_currentIndexChanged(int index)
{
    QString pv = this->group + ":setTriggerSource";
    switch(index)
    {
    case 1:
        Client::writePV(pv, "IMM");
        break;
    case 2:
        Client::writePV(pv, "EXT");
        break;
    case 3:
        Client::writePV(pv, "BUS");
        break;
    }
}

void FormDCCTExpert::onUpdateDcctPlot()
{
    double value = this->pvDcct->get().toDouble();
    if (this->numPoints++ > BUFFER_SIZE)
        this->dcctCurrentValues.removeAt(0);

    this->dcctCurrentValues.push_back(value);

    this->min = *std::min_element(this->dcctCurrentValues.begin(), this->dcctCurrentValues.end());
    this->max = *std::max_element(this->dcctCurrentValues.begin(), this->dcctCurrentValues.end());
    this->margin = 0.05 * (max - min);
    this->chart->axes(Qt::Horizontal).first()->setRange(0, this->dcctCurrentValues.size() - 1);
    this->chart->axes(Qt::Vertical).first()->setRange(min - margin, max + margin);

    int i = 0;
    this->series->clear();
    for (auto v : this->dcctCurrentValues)
        this->series->append(i++, v);

    this->ui->dcctPlot->update();
}
