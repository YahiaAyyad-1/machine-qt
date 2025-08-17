#include "FormVacuumSchematic.h"
#include "ui_FormVacuumSchematic.h"

FormVacuumSchematic::FormVacuumSchematic(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormVacuumSchematic)
{
    ui->setupUi(this);
    CONNECT_CLOSE_BUTTON;

    this->ui->plotIMG->setAutoReplot(true);
    this->ui->plotIMG->setTitle("Gauge Pressure Waveform");
    this->ui->plotIMG->setAxisScale(QwtPlot::xBottom, 1, 27, 1);

    this->ui->plotIP->setAutoReplot(true);
    this->ui->plotIP->setTitle("Ion-Pump Pressure Waveform");
    this->ui->plotIP->setAxisScale(QwtPlot::xBottom, 1, 105, 7);

    QList<double> major;
    QList<double> medium;
    int c = 0;
    for(int i = 1; i <= 16; i++)
    {
        if(i == 3)
            c += 8;
        else if(i % 2 == 0)
            c += 6;
        else
            c += 7;

        if(i == 1)
            medium += 3.5;
        else
            medium += (c - major.last()) / 2.0 + major.last();

        major += c;
    }

    QwtScaleDiv d = this->ui->plotIP->axisScaleDiv(QwtPlot::xBottom);
    d.setTicks(QwtScaleDiv::MajorTick, major);
    d.setTicks(QwtScaleDiv::MediumTick, medium);
    this->ui->plotIP->setAxisScaleDiv(QwtPlot::xBottom, d);
    this->ui->plotIP->setAxisScaleDraw(QwtPlot::xBottom, new QwtAxisTickDraw);

    ui->plotIMG->setAxisScaleDraw(QwtPlot::xBottom, new QwtAxisTickDraw2);

    this->imgCurve = new QwtPlotCurve;
    this->imgCurve->setPen(Qt::black, 1);
    this->imgCurve->setRenderHint(QwtPlotItem::RenderAntialiased);
    this->ipCurve  = new QwtPlotCurve;
    this->ipCurve->setPen(Qt::black, 1);
    this->ipCurve->setRenderHint(QwtPlotItem::RenderAntialiased);

    QwtPlotGrid* gridX = new QwtPlotGrid;
    gridX->setAxes(QwtPlot::xBottom, QwtPlot::yLeft);
    gridX->setPen(Qt::black, 0.25);
    gridX->attach(this->ui->plotIMG);

    QwtPlotGrid* gridY = new QwtPlotGrid;
    gridY->setAxes(QwtPlot::yLeft, QwtPlot::yLeft);
    gridY->setYAxis(QwtPlot::yRight);
    gridY->setPen(Qt::black, 0.25);
    gridY->attach(this->ui->plotIP);

    int ip = 0;
    for(int i = 1; i <= 16; i++)
    {
        if(i == 3) {
            ip = 8;
            for(int c = 1; c <= 5; c++)
                this->pvListIMG.push_back(new QEpicsPV(QString("SRC%1-VA-IMG%2:getPressure").arg(i, 2, 10, QChar('0')).arg(c)));
        }
        else if(i % 2 == 0) {
            ip = 6;
            this->pvListIMG.push_back(new QEpicsPV(QString("SRC%1-VA-IMG1:getPressure").arg(i, 2, 10, QChar('0'))));
        }
        else {
            ip = 7;
            this->pvListIMG.push_back(new QEpicsPV(QString("SRC%1-VA-IMG1:getPressure").arg(i, 2, 10, QChar('0'))));
            this->pvListIMG.push_back(new QEpicsPV(QString("SRC%1-VA-IMG2:getPressure").arg(i, 2, 10, QChar('0'))));
        }

        for(int c = 1; c <= ip; c++)
        {
            this->pvListIP.push_back(new QEpicsPV(QString("SRC%1-VA-IP%2:getPressure").arg(i, 2, 10, QChar('0')).arg(c)));
        }
    }

    foreach (QEpicsPV* pv, this->pvListIMG) {
        QObject::connect(pv, SIGNAL(valueChanged(QVariant)), this, SLOT(imgVacuumChanged()));
    }

    foreach (QEpicsPV* pv, this->pvListIP) {
        QObject::connect(pv, SIGNAL(valueChanged(QVariant)), this, SLOT(ipVacuumChanged()));
    }
}

FormVacuumSchematic::~FormVacuumSchematic()
{
    delete ui;
}

void FormVacuumSchematic::imgVacuumChanged()
{
    double x[27];
    double y[27];
    for(int i = 0; i < 27; i++)
    {
        x[i] = i + 1.0;
        y[i] = this->pvListIMG[i]->get().toDouble();
    }

    this->imgPlotData = new QwtPointArrayData(x, y, 27);
    this->imgCurve->setSamples(this->imgPlotData);
    this->imgCurve->attach(this->ui->plotIMG);
    this->ui->plotIMG->replot();
    this->ui->plotIMG->update();
}

void FormVacuumSchematic::ipVacuumChanged()
{
    double x[105];
    double y[105];
    for(int i = 0; i < 105; i++)
    {
        x[i] = i + 1.0;
        y[i] = this->pvListIP[i]->get().toDouble();
    }

    this->ipPlotData = new QwtPointArrayData(x, y, 105);
    this->ipCurve->setSamples(this->ipPlotData);
    this->ipCurve->attach(this->ui->plotIP);
    this->ui->plotIP->replot();
    this->ui->plotIP->update();
}

QwtAxisTickDraw::QwtAxisTickDraw(double factor) : QwtScaleDraw()
{
    Q_UNUSED(factor);
}

QwtText QwtAxisTickDraw::label(double value) const
{
    if(value == 7)
        return QwtScaleDraw::label(1);
    else if(value == 13)
        return QwtScaleDraw::label(2);
    else if(value == 21)
        return QwtScaleDraw::label(3);
    else if(value == 27)
        return QwtScaleDraw::label(4);
    else if(value == 34)
        return QwtScaleDraw::label(5);
    else if(value == 40)
        return QwtScaleDraw::label(6);
    else if(value == 47)
        return QwtScaleDraw::label(7);
    else if(value == 53)
        return QwtScaleDraw::label(8);
    else if(value == 60)
        return QwtScaleDraw::label(9);
    else if(value == 66)
        return QwtScaleDraw::label(10);
    else if(value == 73)
        return QwtScaleDraw::label(11);
    else if(value == 79)
        return QwtScaleDraw::label(12);
    else if(value == 86)
        return QwtScaleDraw::label(13);
    else if(value == 92)
        return QwtScaleDraw::label(14);
    else if(value == 99)
        return QwtScaleDraw::label(15);
    else if(value == 105)
        return QwtScaleDraw::label(16);

    return QwtScaleDraw::label(0);
}

QwtAxisTickDraw2::QwtAxisTickDraw2(double factor) : QwtScaleDraw()
{
    Q_UNUSED(factor);
}

QwtText QwtAxisTickDraw2::label(double value) const
{
    if(value <= 2)
        return QwtScaleDraw::label(1 + value * 0.1);
    else if(value == 3)
        return QwtScaleDraw::label(2);
    else if(value <= 8 && value > 0)
        return QwtScaleDraw::label(3 + (value - 3) * 0.1);
    else if(value == 9)
        return QwtScaleDraw::label(4);
    else if(value <= 11)
        return QwtScaleDraw::label(5 + (value - 9) * 0.1);
    else if(value == 12)
        return QwtScaleDraw::label(6);
    else if(value <= 14)
        return QwtScaleDraw::label(7 + (value - 12) * 0.1);
    else if(value == 15)
        return QwtScaleDraw::label(8);
    else if(value <= 17)
        return QwtScaleDraw::label(9 + (value - 15) * 0.1);
    else if(value == 18)
        return QwtScaleDraw::label(10);
    else if(value <= 20)
        return QwtScaleDraw::label(11 + (value - 18) * 0.1);
    else if(value == 21)
        return QwtScaleDraw::label(12);
    else if(value <= 23)
        return QwtScaleDraw::label(13 + (value - 21) * 0.1);
    else if(value == 24)
        return QwtScaleDraw::label(14);
    else if(value <= 26)
        return QwtScaleDraw::label(15 + (value - 24) * 0.1);
    else if(value == 27)
        return QwtScaleDraw::label(16);
    else
        return QwtScaleDraw::label(0);
}
