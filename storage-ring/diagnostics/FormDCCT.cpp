#include "FormDCCT.h"
#include "ui_FormDCCT.h"

#define BUFFER_SIZE 60

FormDCCT::FormDCCT(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormDCCT)
{
    ui->setupUi(this);
    CONNECT_CLOSE_BUTTON;

    this->pvDcct = new QEpicsPV("SRC01-DI-DCCT1:getDcctCurrent");

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

FormDCCT::~FormDCCT()
{
    delete ui;
}

void FormDCCT::onUpdateDcctPlot()
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
