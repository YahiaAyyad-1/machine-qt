#include "formpicoplot.h"
#include "ui_formpicoplot.h"

FormPicoPlot::FormPicoPlot(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormPicoPlot)
{
    ui->setupUi(this);
    QObject::connect(ui->boxChannel1, SIGNAL(clicked(bool)), this, SLOT(plot_channel_one(bool)));
    QObject::connect(ui->boxChannel2, SIGNAL(clicked(bool)), this, SLOT(plot_channel_two(bool)));
    QObject::connect(ui->boxChannel3, SIGNAL(clicked(bool)), this, SLOT(plot_channel_three(bool)));
    QObject::connect(ui->boxChannel4, SIGNAL(clicked(bool)), this, SLOT(plot_channel_four(bool)));
    CONNECT_CLOSE_BUTTON;
}

FormPicoPlot::~FormPicoPlot()
{
    delete ui;
}

void FormPicoPlot::plot_channel_one(bool checked)
{
    if(checked)
    {
        ui->plotChannels->setVariableName1Property("I10FE-DI-PA:getCurrent1");
        ui->plotChannels->setTraceLegend1("Channel 1");
    }
    else
    {
        ui->plotChannels->setVariableName1Property(NULL);
    }
}

void FormPicoPlot::plot_channel_two(bool checked)
{
    if(checked)
    {
        ui->plotChannels->setVariableName2Property("I10FE-DI-PA:getCurrent2");
        ui->plotChannels->setTraceLegend2("Channel 2");
    }
    else
    {
        ui->plotChannels->setVariableName2Property(NULL);
    }
}

void FormPicoPlot::plot_channel_three(bool checked)
{
    if(checked)
    {
        ui->plotChannels->setVariableName3Property("I10FE-DI-PA:getCurrent3");
        ui->plotChannels->setTraceLegend3("Channel 3");
    }
    else
    {
        ui->plotChannels->setVariableName3Property(NULL);
    }
}

void FormPicoPlot::plot_channel_four(bool checked)
{
    if(checked)
    {
        ui->plotChannels->setVariableName4Property("I10FE-DI-PA:getCurrent4");
        ui->plotChannels->setTraceLegend4("Channel 4");
    }
    else
    {
        ui->plotChannels->setVariableName4Property(NULL);
    }
}
