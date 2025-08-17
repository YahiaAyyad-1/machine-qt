#include "formbeatspicoammeter.h"
#include "ui_formbeatspicoammeter.h"

FormBeatsPicoammeter::FormBeatsPicoammeter(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormBeatsPicoammeter)
{
    ui->setupUi(this);
//    activeChannels = new QEpicsPV("BEATS-AH501:getChannelsNumber.RVAL");
//    scanRate = new QEpicsPV("BEATS-AH501:ScanRate.SCAN");

    // QObject::connect(activeChannels, SIGNAL(valueChanged(QVariant)), this, SLOT(checkActiveChannels()));
    // QObject::connect(scanRate, SIGNAL(valueChanged(QVariant)), this, SLOT(checkScanRate()));

    this->plot = NULL;
    this->plotPosition = NULL;
    this->plotOffset = NULL;
    CONNECT_CLOSE_BUTTON;
}

FormBeatsPicoammeter::~FormBeatsPicoammeter()
{
    delete ui;
}

void FormBeatsPicoammeter::checkActiveChannels()
{
   int checkChannels = this->activeChannels->get().toInt();

   if (checkChannels == 1)
   {
       ui->lblCH2->setDisabled(true);
       ui->lblCH3->setDisabled(true);
       ui->lblCH4->setDisabled(true);
   }
   else if (checkChannels == 2)
   {
       ui->lblCH2->setDisabled(false);
       ui->lblCH3->setDisabled(true);
       ui->lblCH4->setDisabled(true);
   }
   else
   {
       ui->lblCH2->setDisabled(false);
       ui->lblCH3->setDisabled(false);
       ui->lblCH4->setDisabled(false);
   }
}

void FormBeatsPicoammeter::checkScanRate()
{
    QString scanRateVal = this->scanRate->get().toString();
    Client::writePV("BEATS-AH501:getCalculatedCurrent.SCAN", scanRateVal);
    Client::writePV("BEATS-AH501:getCh1Val.SCAN", scanRateVal);
    Client::writePV("BEATS-AH501:getCh2Val.SCAN", scanRateVal);
    Client::writePV("BEATS-AH501:getCh3Val.SCAN", scanRateVal);
    Client::writePV("BEATS-AH501:getCh4Val.SCAN", scanRateVal);
    Client::writePV("BEATS-AH501:getCalculatedCh1Val.SCAN", scanRateVal);
    Client::writePV("BEATS-AH501:getCalculatedCh2Val.SCAN", scanRateVal);
    Client::writePV("BEATS-AH501:getCalculatedCh3Val.SCAN", scanRateVal);
    Client::writePV("BEATS-AH501:getCalculatedCh4Val.SCAN", scanRateVal);
    Client::writePV("BEATS-AH501:claculateKValue.SCAN", scanRateVal);
    Client::writePV("BEATS-AH501:sumCurrentOffset.SCAN", scanRateVal);
    Client::writePV("BEATS-AH501:sumCh1Ch2.SCAN", scanRateVal);
}

void FormBeatsPicoammeter::on_pushButton_clicked()
{
    OPEN_UI(this->plot, FormPicoPlot, this);
}

void FormBeatsPicoammeter::on_btnPlotPosition_clicked()
{
     OPEN_UI(this->plotPosition, FormPicoPosition, this);
}

void FormBeatsPicoammeter::on_btnChOffset_clicked()
{
    OPEN_UI(this->plotOffset, FormPicoPlotOffset, this);
}
