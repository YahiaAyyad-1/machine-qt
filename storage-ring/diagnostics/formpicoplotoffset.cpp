#include "formpicoplotoffset.h"
#include "ui_formpicoplotoffset.h"

FormPicoPlotOffset::FormPicoPlotOffset(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormPicoPlotOffset)
{
    ui->setupUi(this);
    QObject::connect(ui->boxChannel1, SIGNAL(clicked(bool)), this, SLOT(plot_channel_one(bool)));
    QObject::connect(ui->boxChannel2, SIGNAL(clicked(bool)), this, SLOT(plot_channel_two(bool)));
    QObject::connect(ui->boxChannel3, SIGNAL(clicked(bool)), this, SLOT(plot_channel_three(bool)));
    QObject::connect(ui->boxChannel4, SIGNAL(clicked(bool)), this, SLOT(plot_channel_four(bool)));
    CONNECT_CLOSE_BUTTON;
}

FormPicoPlotOffset::~FormPicoPlotOffset()
{
    delete ui;
}

void FormPicoPlotOffset::plot_channel_one(bool checked)
{
    if(checked)
    {
        ui->plotChannels->setVariableName1Property("BEATS-AH501:sumCurrentOffset.I");
        ui->plotChannels->setTraceLegend1("Channel 1");
    }
    else
    {
        ui->plotChannels->setVariableName1Property(NULL);
    }
}

void FormPicoPlotOffset::plot_channel_two(bool checked)
{
    if(checked)
    {
        ui->plotChannels->setVariableName2Property("BEATS-AH501:sumCurrentOffset.J");
        ui->plotChannels->setTraceLegend2("Channel 2");
    }
    else
    {
        ui->plotChannels->setVariableName2Property(NULL);
    }
}

void FormPicoPlotOffset::plot_channel_three(bool checked)
{
    if(checked)
    {
        ui->plotChannels->setVariableName3Property("BEATS-AH501:sumCurrentOffset.K");
        ui->plotChannels->setTraceLegend3("Channel 3");
    }
    else
    {
        ui->plotChannels->setVariableName3Property(NULL);
    }
}

void FormPicoPlotOffset::plot_channel_four(bool checked)
{
    if(checked)
    {
        ui->plotChannels->setVariableName4Property("BEATS-AH501:sumCurrentOffset.L");
        ui->plotChannels->setTraceLegend4("Channel 4");
    }
    else
    {
        ui->plotChannels->setVariableName4Property(NULL);
    }
}
