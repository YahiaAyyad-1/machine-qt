#include "FormWaveformSettings.h"
#include "ui_FormWaveformSettings.h"

FormWaveformSettings::FormWaveformSettings(QString magnet, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormWaveformSettings)
{
    ui->setupUi(this);
    this->group = magnet;

    SET_GROUP(QELabel);
    SET_GROUP(QENumericEdit);
    SET_GROUP(QEPushButton);
    SET_GROUP(QEPlot);
    for(int i = 0; i < 4; i++)
    {
        QObject::connect(this->findChild<QPushButton*>(QString::asprintf("btnUpload%d", i)), SIGNAL(clicked(bool)), this, SLOT(waveformUpload_Clicked()));
        QObject::connect(this->findChild<QPushButton*>(QString::asprintf("btnSelect%d", i)), SIGNAL(clicked(bool)), this, SLOT(waveformSelect_Clicked()));
    }

    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
    this->setWindowTitle(group + " Waveform Settings");
}

FormWaveformSettings::~FormWaveformSettings()
{
    delete ui;
}

void FormWaveformSettings::waveformUpload_Clicked()
{
    QPushButton* button = (QPushButton*) sender();
    QString name = button->objectName();
    QChar id = name[name.length() - 1];
    QString pvName = this->group + ":setWaveform" + id;
    QString fileName = this->findChild<QLineEdit*>("txtFile" + name[name.length() - 1])->text();
    if(fileName.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Select waveform first");
        return;
    }

    float waveform[WAVEFORM_SIZE] = {0};
    QFile _file(fileName);
    if(!_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Warning", "Could not open waveform file " + fileName);
        return;
    }

    QTextStream waveformFile(&_file);
    int i = 0;
    while(!waveformFile.atEnd() && i < WAVEFORM_SIZE) {
        waveform[i] = waveformFile.readLine().trimmed().toFloat();
        i++;
    }

    int status;
    chid pvID;

    ca_search(pvName.toStdString().c_str(), &pvID);
    status = ca_pend_io(1);
    if(status != ECA_NORMAL)
    {
        SEVCHK(status, "ca_pend_io error");
        QMessageBox::warning(NULL, "Error writing to PV", "Could not write the value to PV: " + pvName);
        return;
    }

    ca_array_put(DBR_FLOAT, WAVEFORM_SIZE, pvID, waveform);

    Client::writePV(this->group + ":getWaveform" + id + ".PROC", 1);

    _file.close();
}

void FormWaveformSettings::waveformSelect_Clicked()
{
    QPushButton* button = (QPushButton*) sender();
    QString name = button->objectName();
    QString fileName = QFileDialog::getOpenFileName(this, "Select Waveform file", getenv("HOME"));
    if(fileName.isEmpty()) {
        QMessageBox::warning(this, "Warning", "No waveform selected");
        return;
    }

    this->findChild<QLineEdit*>("txtFile" + name[name.length() - 1])->setText(fileName);
}
