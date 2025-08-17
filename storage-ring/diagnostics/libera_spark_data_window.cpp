#include "libera_spark_data_window.h"
#include "ui_libera_spark_data_window.h"

LiberaSparkDataWindow::LiberaSparkDataWindow(QString prefix, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LiberaSparkDataWindow)
{
    ui->setupUi(this);
    QObject::connect(this->ui->btnClose, SIGNAL(clicked()), this, SLOT(onClose()));
    // this->setAttribute(Qt::WA_DeleteOnClose);

    this->prefix = prefix;
    QString dataSet = prefix.split(":")[1];
    QString sizePV  = prefix + ":Size";
    ui->lblTitle->setText(dataSet);
    ui->txtBuffer->setVariableNameProperty(sizePV);
    Client::writePV(prefix + ".DISA", 0);

    if(dataSet == "TBT_QSUM" || dataSet == "TBT_QSUM_DEC" || dataSet == "TDP_QSUM" || dataSet == "TDP_QSUM_DEC") {
        ui->plot->setSizePVA(sizePV);
        ui->plot->setSizePVB(sizePV);

        ui->plot->setDataPVA(prefix + ":Q");
        ui->plot->setDataPVB(prefix + ":SUM");

        ui->plot->setAliasA("Q");
        ui->plot->setAliasB("Sum");
    }
    else if(dataSet == "TBT_XY" || dataSet == "TBT_XY_DEC" || dataSet == "TDP_XY" || dataSet == "TDP_XY_DEC") {
        ui->plot->setSizePVA(sizePV);
        ui->plot->setSizePVB(sizePV);

        ui->plot->setDataPVA(prefix + ":X");
        ui->plot->setDataPVB(prefix + ":Y");

        ui->plot->setAliasA("TBT X");
        ui->plot->setAliasB("TBT Y");
    }
    else if(dataSet == "ADC" || dataSet == "TBT_AMPL" || dataSet == "TBT_AMPL_DEC" || dataSet == "TDP_AMPL" || dataSet == "TDP_AMPL_DEC") {
        ui->plot->setSizePVA(sizePV);
        ui->plot->setSizePVB(sizePV);
        ui->plot->setSizePVC(sizePV);
        ui->plot->setSizePVD(sizePV);

        ui->plot->setDataPVA(prefix + ":A");
        ui->plot->setDataPVB(prefix + ":B");
        ui->plot->setDataPVC(prefix + ":C");
        ui->plot->setDataPVD(prefix + ":D");

        ui->plot->setAliasA("Channel A");
        ui->plot->setAliasB("Channel B");
        ui->plot->setAliasC("Channel C");
        ui->plot->setAliasD("Channel D");
    }
    else if(dataSet == "TBT_IQ" || dataSet == "TBT_IQ_DEC") {
        ui->plot->setSizePVA(sizePV);
        ui->plot->setSizePVB(sizePV);
        ui->plot->setSizePVC(sizePV);
        ui->plot->setSizePVD(sizePV);
        ui->plot->setSizePVE(sizePV);
        ui->plot->setSizePVF(sizePV);
        ui->plot->setSizePVG(sizePV);
        ui->plot->setSizePVH(sizePV);

        ui->plot->setDataPVA(prefix + ":IA");
        ui->plot->setDataPVB(prefix + ":QA");
        ui->plot->setDataPVC(prefix + ":IB");
        ui->plot->setDataPVD(prefix + ":QB");
        ui->plot->setDataPVE(prefix + ":IC");
        ui->plot->setDataPVF(prefix + ":QC");
        ui->plot->setDataPVG(prefix + ":ID");
        ui->plot->setDataPVH(prefix + ":QD");

        ui->plot->setAliasA("Channel IA");
        ui->plot->setAliasB("Channel QA");
        ui->plot->setAliasC("Channel IB");
        ui->plot->setAliasD("Channel QB");
        ui->plot->setAliasE("Channel IC");
        ui->plot->setAliasF("Channel QC");
        ui->plot->setAliasG("Channel ID");
        ui->plot->setAliasH("Channel QD");
    }
}

LiberaSparkDataWindow::~LiberaSparkDataWindow()
{
    delete ui;
}

void LiberaSparkDataWindow::onClose()
{
    Client::writePV(prefix + ".DISA", 1);
    std::cout << "Debug " << prefix.toStdString() << std::endl;
    this->close();
}

void LiberaSparkDataWindow::closeEvent(QCloseEvent *event)
{
    Client::writePV(prefix + ".DISA", 1);
    std::cout << "Debug " << prefix.toStdString() << std::endl;
    event->accept();
}
