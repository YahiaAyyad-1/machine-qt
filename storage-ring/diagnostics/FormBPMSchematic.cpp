#include "FormBPMSchematic.h"
#include "ui_FormBPMSchematic.h"

FormBPMSchematic::FormBPMSchematic(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormBPMSchematic)
{
    ui->setupUi(this);
    CONNECT_CLOSE_BUTTON;

    for(int i = 1; i <= 12; i++)
    {
        for(int j = 1; j <= 4; j++)
        {
            QESimpleShape* led = this->findChild<QESimpleShape*>("led_" + QString::number(j + 4 * (i - 1)));
            led->setVariableNameSubstitutionsProperty(QString::asprintf("l=%d,b=%d", i, j));
            this->xData.push_back(new QEpicsPV(QString::asprintf("SR-DI-LBR%d-bpm%d:getSlowAcquisitionXScale", i, j)));
            this->yData.push_back(new QEpicsPV(QString::asprintf("SR-DI-LBR%d-bpm%d:getSlowAcquisitionYScale", i, j)));
			QObject::connect(this->xData[j + 4*(i-1) - 1], SIGNAL(valueChanged(QVariant)), this, SLOT(horizontalDataChanged()));
            QObject::connect(this->yData[j + 4*(i-1) - 1], SIGNAL(valueChanged(QVariant)), this, SLOT(verticalDataChanged()));
        }
    }

    this->ui->plotX->setAutoReplot(true);
    this->ui->plotY->setAutoReplot(true);
    this->xCurve = new QwtPlotCurve("Horizontal Data");
    this->yCurve = new QwtPlotCurve("Vertical Data");
    this->xCurve->setPen(Qt::black, 1);
    this->yCurve->setPen(Qt::black, 1);

    this->ui->plotX->setAxisScale(QwtPlot::xBottom, 1, 48, 4);
    this->ui->plotY->setAxisScale(QwtPlot::xBottom, 1, 48, 4);

    QwtPlotGrid* gridX = new QwtPlotGrid;
    gridX->setAxes(QwtPlot::xBottom, QwtPlot::yLeft);
    gridX->setPen(Qt::black, 0.25);
    gridX->attach(this->ui->plotX);

    QwtPlotGrid* gridY = new QwtPlotGrid;
    gridY->setAxes(QwtPlot::xBottom, QwtPlot::yLeft);
    gridY->setPen(Qt::black, 0.25);
    gridY->attach(this->ui->plotY);

    QFile file(":/configurations/bpms.txt");
    if(!file.open(QFile::ReadOnly | QFile::Text))
        return;

    bool ok[3];
    int id, libera, bpm;
    QStringList items;
    QString line, _libera;
    QTextStream bpms(&file);
    while(!bpms.atEnd()) {
        line = bpms.readLine();
        items = line.split(" ");
        id = items[0].toInt(&ok[0]);
        _libera = items[1];

        if(!ok[0]) {
            this->findChild<QEPushButton*>("btnBPM_" + STRING(id))->setText(STRING(id));
            return;
        }

        QEPushButton* button = this->findChild<QEPushButton*>("btnBPM_" + STRING(id));
        QESimpleShape* led = this->findChild<QESimpleShape*>("led_" + STRING(id));
        if(_libera == "NC") {
            button->setText("NC");
            button->setEnabled(false);
            led->setVisible(false);
        }
        else {
            libera = items[1].toInt(&ok[1]);
            bpm = items[2].toInt(&ok[2]);
            button->setText(STRING(id));
            button->setProgram("libera qt bpm " + STRING(libera) + " " + STRING(bpm));
            led->setVariableNameProperty(QString("SR-DI-LBR%1-BPM%2:getInterlocks").arg(libera).arg(bpm));
            if(items.count() == 4 && items[3] == "GDX") {
                QPalette p = button->palette();
                p.setColor(QPalette::Button, Qt::yellow);
                button->setAutoFillBackground(true);
                button->setPalette(p);
                button->update();
            }
        }

        if(!ok[0] || !ok[1] || !ok[2]) {
            QMessageBox::warning(this, "Error", "Invalid BPMs configuration file");
        }
    }
}

FormBPMSchematic::~FormBPMSchematic()
{
    delete ui;
}

void FormBPMSchematic::horizontalDataChanged()
{
    double x[48];
    double y[48];
    for(int i = 0; i < 48; i++) {
        x[i] = i + 1.0;
        y[i] = this->xData[i]->get().toDouble();
    }

    this->xPlotData = new QwtPointArrayData(x, y, 48);
    this->xCurve->setSamples(this->xPlotData);
    this->xCurve->attach(this->ui->plotX);
    this->ui->plotX->replot();
    this->ui->plotX->update();
}

void FormBPMSchematic::verticalDataChanged()
{
    QVector<double> x;
    QVector<double> y;
    for(int i = 0; i < 48; i++) {
        x.push_back(i + 1.0);
        y.push_back(this->yData[i]->get().toDouble());
    }

    this->yPlotData = new QwtPointArrayData(x, y);
    this->yCurve->setSamples(this->yPlotData);
    this->yCurve->attach(this->ui->plotY);
    this->ui->plotY->replot();
    this->ui->plotY->update();
}
