#include "FormGeneralTuning.h"
#include "ui_FormGeneralTuning.h"

FormGeneralTuning::FormGeneralTuning(QString magnet, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormGeneralTuning)
{
    ui->setupUi(this);
    this->magnet = magnet;
    this->setWindowTitle(this->magnet + " Tuning");
    CONNECT_CLOSE_BUTTON;
}

FormGeneralTuning::~FormGeneralTuning()
{
    delete ui;
}

void FormGeneralTuning::setValue(QString command, float value)
{
    int gw = 0;
    int ch = 0;
    if(this->magnet == "QF")
    {
        for(gw = 0; gw <= 3; gw++)
        {
            for(ch = 0; ch <= 14; ch += 2)
                Client::writePV(QString("SR-PS-GW%1-CH%2:" + command).arg(gw).arg(ch), value);
        }
    }
    else if(this->magnet == "QD")
    {
        for(gw = 0; gw <= 3; gw++)
        {
            for(ch = 1; ch <= 15; ch += 2)
                Client::writePV(QString("SR-PS-GW%1-CH%2:" + command).arg(gw).arg(ch), value);
        }
    }
    else if(this->magnet == "SF")
    {
        Client::writePV("SR-PS-GW4-CH12:" + command, command);
        Client::writePV("SR-PS-GW4-CH14:" + command, command);
    }
    else if(this->magnet == "SD")
    {
        Client::writePV("SR-PS-GW4-CH13:" + command, command);
        Client::writePV("SR-PS-GW4-CH15:" + command, command);
    }
    else
        return;
}

void FormGeneralTuning::on_pushButton_clicked()
{
    setValue(":setKp", ui->txtKP->text().toFloat());
}

void FormGeneralTuning::on_pushButton_2_clicked()
{
    setValue(":setKi", ui->txtKI->text().toFloat());
}

void FormGeneralTuning::on_pushButton_3_clicked()
{
    setValue(":setI2vGain", ui->txtI2VGain->text().toFloat());
}

void FormGeneralTuning::on_pushButton_4_clicked()
{
    setValue(":setOffsetError", ui->txtOffsetError->text().toFloat());
}

void FormGeneralTuning::on_pushButton_8_clicked()  { setValue(":setGainError", ui->txtGainError->text().toFloat()); }

void FormGeneralTuning::on_pushButton_6_clicked()  { setValue(":setMinIref", ui->txtMinIref->text().toFloat()); }

void FormGeneralTuning::on_pushButton_5_clicked()  { setValue(":setMaxIref", ui->txtMaxIref->text().toFloat()); }

void FormGeneralTuning::on_pushButton_7_clicked()  { setValue(":setMindIdt", ui->txtMindIdt->text().toFloat()); }

void FormGeneralTuning::on_pushButton_12_clicked() { setValue(":setMaxdIdt", ui->txtMaxdIdt->text().toFloat()); }

void FormGeneralTuning::on_pushButton_16_clicked() { setValue(":setMinEtotal", ui->txtMinTotalE->text().toFloat()); }

void FormGeneralTuning::on_pushButton_13_clicked() { setValue(":setMaxEtotal", ui->txtMaxTotalE->text().toFloat()); }

void FormGeneralTuning::on_pushButton_10_clicked() { setValue(":setInterlockVmon", ui->txtInterlockVoltage->text().toFloat()); }

void FormGeneralTuning::on_pushButton_9_clicked()  { setValue(":setInterlockIload", ui->txtInterlockIload->text().toFloat()); }

void FormGeneralTuning::on_pushButton_14_clicked() { setValue(":setInterlockIearth", ui->txtInterlockIEartth->text().toFloat()); }

void FormGeneralTuning::on_pushButton_15_clicked() { setValue(":setInterlockdIdt", ui->txtInterlockdIdt->text().toFloat()); }

void FormGeneralTuning::on_pushButton_11_clicked() { setValue(":setInterlockError", ui->txtInterlockError->text().toFloat()); }

void FormGeneralTuning::on_pushButton_17_clicked() { setValue(":setInterlockTemperature", ui->txtInterlockTemp->text().toFloat()); }

void FormGeneralTuning::on_pushButton_18_clicked() { setValue(":setInterlockMask", ui->txtInterlockMask->text().toFloat()); }
