#include "FormBpmConfig.h"
#include "ui_FormBpmConfig.h"

FormBpmConfig::FormBpmConfig(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormBpmConfig)
{
    ui->setupUi(this);
    CONNECT_CLOSE_BUTTON;
    FIX_SIZE;

    ui->txtGain->setValidator(new QIntValidator(-100, 100, this));
    this->BPM0Min = new QEpicsPV("libera8:bpm3:ilk:limits:min_x_mon");
    this->BPM0Max = new QEpicsPV("libera8:bpm3:ilk:limits:max_x_mon");
    this->BPM1Min = new QEpicsPV("libera8:bpm4:ilk:limits:min_x_mon");
    this->BPM1Max = new QEpicsPV("libera8:bpm4:ilk:limits:max_x_mon");
    this->BPM2Min = new QEpicsPV("libera9:bpm1:ilk:limits:min_x_mon");
    this->BPM2Max = new QEpicsPV("libera9:bpm1:ilk:limits:max_x_mon");
    this->BPM3Min = new QEpicsPV("libera9:bpm2:ilk:limits:min_x_mon");
    this->BPM3Max = new QEpicsPV("libera9:bpm2:ilk:limits:max_x_mon");
    QObject::connect(BPM0Min, SIGNAL(valueChanged(QVariant)), this, SLOT(on_lblBPM0Min_dbValueChanged()));
    QObject::connect(BPM0Max, SIGNAL(valueChanged(QVariant)), this, SLOT(on_lblBPM0Max_dbValueChanged()));
    QObject::connect(BPM1Min, SIGNAL(valueChanged(QVariant)), this, SLOT(on_lblBPM1Min_dbValueChanged()));
    QObject::connect(BPM1Max, SIGNAL(valueChanged(QVariant)), this, SLOT(on_lblBPM1Max_dbValueChanged()));
    QObject::connect(BPM2Min, SIGNAL(valueChanged(QVariant)), this, SLOT(on_lblBPM2Min_dbValueChanged()));
    QObject::connect(BPM2Max, SIGNAL(valueChanged(QVariant)), this, SLOT(on_lblBPM2Max_dbValueChanged()));
    QObject::connect(BPM3Min, SIGNAL(valueChanged(QVariant)), this, SLOT(on_lblBPM3Min_dbValueChanged()));
    QObject::connect(BPM3Max, SIGNAL(valueChanged(QVariant)), this, SLOT(on_lblBPM3Max_dbValueChanged()));
    QEpicsPV* pv;
    for(int libera = 1; libera <= 12; libera++)
    {
        for(int bpm = 1; bpm <= 4; bpm++)
        {
            pv = new QEpicsPV(QString("libera%1:bpm%2:ilk:enabled_mon").arg(libera).arg(bpm));
            QObject::connect(pv, SIGNAL(valueChanged(QVariant)), this, SLOT(interlocksChanged()));
            interlocksPVs.push_back(pv);

            pv = new QEpicsPV(QString("libera%1:bpm%2:ilk:gain_dependent:enabled_mon").arg(libera).arg(bpm));
            QObject::connect(pv, SIGNAL(valueChanged(QVariant)), this, SLOT(gainEnabledChanged()));
            gainPVs.push_back(pv);

            pv = new QEpicsPV(QString("SR-DI-LBR%1-BPM%2:getInterlocks").arg(libera).arg(bpm));
            QObject::connect(pv, SIGNAL(valueChanged(QVariant)), this, SLOT(interlocksCountChanged()));
            pvInterlocked.push_back(pv);

            pv = new QEpicsPV(QString("libera%1:bpm%2:ilk:limits:min_x_mon").arg(libera).arg(bpm));
            QObject::connect(pv, SIGNAL(valueChanged(QVariant)), this, SLOT(positionLimitsChanged()));
            pvMinX.push_back(pv);

            pv = new QEpicsPV(QString("libera%1:bpm%2:ilk:limits:max_x_mon").arg(libera).arg(bpm));
            QObject::connect(pv, SIGNAL(valueChanged(QVariant)), this, SLOT(positionLimitsChanged()));
            pvMaxX.push_back(pv);

            pv = new QEpicsPV(QString("libera%1:bpm%2:ilk:limits:min_y_mon").arg(libera).arg(bpm));
            QObject::connect(pv, SIGNAL(valueChanged(QVariant)), this, SLOT(positionLimitsChanged()));
            pvMinY.push_back(pv);

            pv = new QEpicsPV(QString("libera%1:bpm%2:ilk:limits:max_y_mon").arg(libera).arg(bpm));
            QObject::connect(pv, SIGNAL(valueChanged(QVariant)), this, SLOT(positionLimitsChanged()));
            pvMaxY.push_back(pv);
        }
    }
}

FormBpmConfig::~FormBpmConfig()
{
    delete ui;
}

void FormBpmConfig::on_btnInterlockEnable_clicked()
{
    setParameter("enabled_sp", 1);
}

void FormBpmConfig::on_btnInterlockDisable_clicked()
{
    setParameter("enabled_sp", 0);
}

void FormBpmConfig::on_btnGainEnable_clicked()
{
    setParameter("gain_dependent:enabled_sp", 1);
}

void FormBpmConfig::on_btnGainDisable_clicked()
{
    setParameter("gain_dependent:enabled_sp", 0);
}

void FormBpmConfig::on_btnSetAtt_clicked()
{
    setParameter("gain_dependent:threshold_sp", ui->txtGain->text().toDouble());
}

void FormBpmConfig::on_btnSetMinX_clicked()
{
    setParameter("limits:min_x_sp", ui->txtMinX->text().toDouble() * 1E6);
}

void FormBpmConfig::on_btnSetMaxX_clicked()
{
    setParameter("limits:max_x_sp", ui->txtMaxX->text().toDouble() * 1E6);
}

void FormBpmConfig::on_btnSetMinY_clicked()
{
    setParameter("limits:min_y_sp", ui->txtMinY->text().toDouble() * 1E6);
}

void FormBpmConfig::on_btnSetMaxY_clicked()
{
    setParameter("limits:max_y_sp", ui->txtMaxY->text().toDouble() * 1E6);
}

void FormBpmConfig::on_btnSetOVF_clicked()
{
    setParameter("limits:ovf_threshold_sp", ui->txtOVF->text().toDouble());
}

void FormBpmConfig::on_btnSetOVFTime_clicked()
{
    setParameter("limits:ovf_duration_sp", ui->txtOVFTime->text().toDouble());
}

void FormBpmConfig::on_btnSetfilter_clicked()
{
    setParameter("filter:position_sp", ui->txtFilter->text().toDouble());
}

void FormBpmConfig::on_btnSetLimit_clicked()
{
    setParameter("filter:overflow_sp", ui->txtLimit->text().toDouble());
}

void FormBpmConfig::interlocksChanged()
{
    int count = 0;
    foreach (QEpicsPV* pv, interlocksPVs) {
        if(pv->get().toBool())
            count++;
    }

    ui->ledILK->setValue(0);
    if(count == 48)
    {
        ui->ledILK->setColour0Property(Qt::green);
    }
    else if(count < 48 && count > 0)
    {
        ui->ledILK->setColour0Property(Qt::yellow);
    }
    else
        ui->ledILK->setColour0Property(COLOR_DARKGREEN);
}

void FormBpmConfig::gainEnabledChanged()
{
    int count = 0;
    foreach (QEpicsPV* pv, gainPVs) {
        if(pv->get().toBool())
            count++;
    }

    ui->ledGain->setValue(0);
    if(count == 48)
    {
        ui->ledGain->setColour0Property(Qt::green);
    }
    else if(count < 48 && count > 0)
    {
        ui->ledGain->setColour0Property(Qt::yellow);
    }
    else
        ui->ledGain->setColour0Property(COLOR_DARKGREEN);
}

void FormBpmConfig::setParameter(QString parameter, int value)
{
    for(int libera = 1; libera <= 12; libera++)
    {
        for(int bpm = 1; bpm <= 4; bpm++)
        {
            Client::writePV(QString("libera%1:bpm%2:ilk:%3").arg(libera).arg(bpm).arg(parameter), value);
        }
    }
}

void FormBpmConfig::setParameter(QString parameter, double value)
{
    for(int libera = 1; libera <= 12; libera++)
    {
        for(int bpm = 1; bpm <= 4; bpm++)
        {
            Client::writePV(QString("libera%1:bpm%2:ilk:%3").arg(libera).arg(bpm).arg(parameter), value);
        }
    }
}

void FormBpmConfig::interlocksCountChanged()
{
    int count = 0;
    foreach (QEpicsPV* pv, pvInterlocked) {
        if(pv->get().toInt() == 1)
            count++;
    }
    ui->lblCount->setText(QString::number(count));
}

void FormBpmConfig::on_btnReset_clicked()
{
    setParameter("status:reset_sp", 0);
}

void FormBpmConfig::positionLimitsChanged()
{
    int sum = 0;
    double avg = 0;

    foreach (QEpicsPV* pv, this->pvMinX) {
        sum += pv->get().toInt();
    }
    avg = sum / 48.0 / 1000000.0;
    ui->lblMinX->setText(QString::asprintf("%1.3f", avg));

    sum = 0;
    foreach (QEpicsPV* pv, this->pvMaxX) {
        sum += pv->get().toInt();
    }
    avg = sum / 48.0 / 1000000.0;
    ui->lblMaxX->setText(QString::asprintf("%1.3f", avg));

    sum = 0;
    foreach (QEpicsPV* pv, this->pvMinY) {
        sum += pv->get().toInt();
    }
    avg = sum / 48.0 / 1000000.0;
    ui->lblMinY->setText(QString::asprintf("%1.3f", avg));

    sum = 0;
    foreach (QEpicsPV* pv, this->pvMaxY) {
        sum += pv->get().toInt();
    }
    avg = sum / 48.0 / 1000000.0;
    ui->lblMaxY->setText(QString::asprintf("%1.3f", avg));
}

void FormBpmConfig::on_btnSet_clicked()
{
    bool ok[8];
    double values[8];

    values[0] = ui->txtBPM1Min->text().toDouble(&ok[0]);
    values[1] = ui->txtBPM1Max->text().toDouble(&ok[1]);
    values[2] = ui->txtBPM2Min->text().toDouble(&ok[2]);
    values[3] = ui->txtBPM2Max->text().toDouble(&ok[3]);
    values[4] = ui->txtBPM0Min->text().toDouble(&ok[4]);
    values[5] = ui->txtBPM0Max->text().toDouble(&ok[5]);
    values[6] = ui->txtBPM3Min->text().toDouble(&ok[6]);
    values[7] = ui->txtBPM3Max->text().toDouble(&ok[7]);
    if(!ok[0] || !ok[1] || !ok[2] || !ok[3] || !ok[4] || !ok[5] || !ok[6] || !ok[7]) {
        QMessageBox::warning(this, "Error", "Illegal values entered.");
        return;
    }

    Client::writePV("libera8:bpm4:ilk:limits:min_x_sp", ui->txtBPM1Min->text().toDouble() * 1000000.0);
    Client::writePV("libera8:bpm4:ilk:limits:max_x_sp", ui->txtBPM1Max->text().toDouble() * 1000000.0);
    Client::writePV("libera9:bpm1:ilk:limits:min_x_sp", ui->txtBPM2Min->text().toDouble() * 1000000.0);
    Client::writePV("libera9:bpm1:ilk:limits:max_x_sp", ui->txtBPM2Max->text().toDouble() * 1000000.0);

    Client::writePV("libera8:bpm3:ilk:limits:min_x_sp", ui->txtBPM0Min->text().toDouble() * 1000000.0);
    Client::writePV("libera8:bpm3:ilk:limits:max_x_sp", ui->txtBPM0Max->text().toDouble() * 1000000.0);
    Client::writePV("libera9:bpm2:ilk:limits:min_x_sp", ui->txtBPM3Min->text().toDouble() * 1000000.0);
    Client::writePV("libera9:bpm2:ilk:limits:max_x_sp", ui->txtBPM3Max->text().toDouble() * 1000000.0);
}

void FormBpmConfig::on_lblBPM0Min_dbValueChanged()
{
    double device_value = BPM0Min->get().toDouble();
    device_value = device_value/ 1000000.0;
    QString value = QString::number(device_value);
    ui->lblBPM0Min->setText(value);
}

void FormBpmConfig::on_lblBPM0Max_dbValueChanged()
{
    double device_value = BPM0Max->get().toDouble();
    device_value = device_value/ 1000000.0;
    QString value = QString::number(device_value);
    ui->lblBPM0Max->setText(value);
}

void FormBpmConfig::on_lblBPM1Min_dbValueChanged()
{
    double device_value = BPM1Min->get().toDouble();
    device_value = device_value/ 1000000.0;
    QString value = QString::number(device_value);
    ui->lblBPM1Min->setText(value);
}

void FormBpmConfig::on_lblBPM1Max_dbValueChanged()
{
    double device_value = BPM1Max->get().toDouble();
    device_value = device_value/ 1000000.0;
    QString value = QString::number(device_value);
    ui->lblBPM1Max->setText(value);
}

void FormBpmConfig::on_lblBPM2Min_dbValueChanged()
{
    double device_value = BPM2Min->get().toDouble();
    device_value = device_value/ 1000000.0;
    QString value = QString::number(device_value);

    ui->lblBPM2Min->setText(value);
}

void FormBpmConfig::on_lblBPM2Max_dbValueChanged()
{
    double device_value = BPM2Max->get().toDouble();
    device_value = device_value/ 1000000.0;
    QString value = QString::number(device_value);
    ui->lblBPM2Max->setText(value);
}

void FormBpmConfig::on_lblBPM3Min_dbValueChanged()
{
    double device_value = BPM3Min->get().toDouble();
    device_value = device_value/ 1000000.0;
    QString value = QString::number(device_value);
    ui->lblBPM3Min->setText(value);
}

void FormBpmConfig::on_lblBPM3Max_dbValueChanged()
{
    double device_value = BPM3Max->get().toDouble();
    device_value = device_value/ 1000000.0;
    QString value = QString::number(device_value);
    ui->lblBPM3Max->setText(value);
}
