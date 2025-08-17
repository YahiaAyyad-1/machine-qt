#include "libera_spark_window.h"
#include "ui_libera_spark_window.h"

LiberaSparkWindow::LiberaSparkWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LiberaSparkWindow)
{
    ui->setupUi(this);
    CONNECT_CLOSE_BUTTON;

    this->data = NULL;
}

LiberaSparkWindow::~LiberaSparkWindow()
{
    delete ui;
}

void LiberaSparkWindow::on_btnADC_clicked()
{
    OPEN_UI(this->data, LiberaSparkDataWindow, "SR-DI-LBS:ADC", this);
}

void LiberaSparkWindow::on_btnTBTIQ_clicked()
{
    OPEN_UI(this->data, LiberaSparkDataWindow, "SR-DI-LBS:TBT_IQ", this);
}

void LiberaSparkWindow::on_pushButton_3_clicked()
{
    OPEN_UI(this->data, LiberaSparkDataWindow, "SR-DI-LBS:TBT_AMPL", this);
}

void LiberaSparkWindow::on_pushButton_4_clicked()
{
    OPEN_UI(this->data, LiberaSparkDataWindow, "SR-DI-LBS:TBT_QSUM", this);
}

void LiberaSparkWindow::on_pushButton_5_clicked()
{
    OPEN_UI(this->data, LiberaSparkDataWindow, "SR-DI-LBS:TBT_XY", this);
}

void LiberaSparkWindow::on_pushButton_6_clicked()
{
    OPEN_UI(this->data, LiberaSparkDataWindow, "SR-DI-LBS:TBT_IQ_DEC", this);
}

void LiberaSparkWindow::on_pushButton_7_clicked()
{
    OPEN_UI(this->data, LiberaSparkDataWindow, "SR-DI-LBS:TBT_AMPL_DEC", this);
}

void LiberaSparkWindow::on_pushButton_8_clicked()
{
    OPEN_UI(this->data, LiberaSparkDataWindow, "SR-DI-LBS:TBT_QSUM_DEC", this);
}

void LiberaSparkWindow::on_pushButton_9_clicked()
{
    OPEN_UI(this->data, LiberaSparkDataWindow, "SR-DI-LBS:TBT_XY_DEC", this);
}

void LiberaSparkWindow::on_pushButton_15_clicked()
{
    OPEN_UI(this->data, LiberaSparkDataWindow, "SR-DI-LBS:TDP_AMPL", this);
}

void LiberaSparkWindow::on_pushButton_13_clicked()
{
    OPEN_UI(this->data, LiberaSparkDataWindow, "SR-DI-LBS:TDP_QSUM", this);
}

void LiberaSparkWindow::on_pushButton_11_clicked()
{
    OPEN_UI(this->data, LiberaSparkDataWindow, "SR-DI-LBS:TDP_XY", this);
}

void LiberaSparkWindow::on_pushButton_10_clicked()
{
    OPEN_UI(this->data, LiberaSparkDataWindow, "SR-DI-LBS:TDP_AMPL_DEC", this);
}

void LiberaSparkWindow::on_pushButton_12_clicked()
{
    OPEN_UI(this->data, LiberaSparkDataWindow, "SR-DI-LBS:TDP_QSUM_DEC", this);
}

void LiberaSparkWindow::on_pushButton_14_clicked()
{
    OPEN_UI(this->data, LiberaSparkDataWindow, "SR-DI-LBS:TDP_XY_DEC", this);
}
