#include "FormGeneralWaveform.h"
#include "ui_FormGeneralWaveform.h"

FormGeneralWaveform::FormGeneralWaveform(QString magnet, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormGeneralWaveform)
{
    ui->setupUi(this);
    this->group = magnet;
    CONNECT_CLOSE_BUTTON;
    this->setWindowTitle(this->group + " Waveforms");

    for(int i = 1; i <= 4; i++) {
        QObject::connect(this->findChild<QPushButton*>("btnSize_" + QString::number(i)),   SIGNAL(clicked()), this, SLOT(onSizeChanged()));
        QObject::connect(this->findChild<QPushButton*>("btnPeriod_" + QString::number(i)), SIGNAL(clicked()), this, SLOT(onPeriodChanged()));
        QObject::connect(this->findChild<QPushButton*>("btnFinal_" + QString::number(i)),  SIGNAL(clicked()), this, SLOT(onFinalChanged()));
        QObject::connect(this->findChild<QPushButton*>("btnTop_" + QString::number(i)),    SIGNAL(clicked()), this, SLOT(onTopChanged()));
        QObject::connect(this->findChild<QPushButton*>("btnPlot_" + QString::number(i)),   SIGNAL(clicked()), this, SLOT(onPlotClicked()));
        QObject::connect(this->findChild<QPushButton*>("btnSelect_" + QString::number(i)), SIGNAL(clicked()), this, SLOT(onBrowseClicked()));
        QObject::connect(this->findChild<QPushButton*>("btnUpload_" + QString::number(i)), SIGNAL(clicked()), this, SLOT(onUploadClicked()));
    }
}

FormGeneralWaveform::~FormGeneralWaveform()
{
    delete ui;
}

void FormGeneralWaveform::setCommand(QString command, int id)
{
    float value = this->findChild<QLineEdit*>("txt" + command + "_" + STRING(id))->text().toFloat();
    if(this->group == "QF" || this->group == "QD") {
        for(int i = 1; i <= 16; i++) {
            Client::writePV(QString::asprintf("SRC%02d-PS-%s1:setWaveform%d%s", i, this->group.toStdString().c_str(), id - 1, command.toStdString().c_str()), value);
        }
    }
    else {
        Client::writePV(QString::asprintf("SR-PS-%s1:setWaveform%d%s", this->group.toStdString().c_str(), id - 1, command.toStdString().c_str()), value);
        Client::writePV(QString::asprintf("SR-PS-%s2:setWaveform%d%s", this->group.toStdString().c_str(), id - 1, command.toStdString().c_str()), value);
    }
}

void FormGeneralWaveform::onSizeChanged()
{
    QPushButton* button = (QPushButton*) sender();
    int id = button->objectName()[button->objectName().length() - 1].toLatin1() - 0x30;
    setCommand("Size", id);
}

void FormGeneralWaveform::onPeriodChanged()
{
    QPushButton* button = (QPushButton*) sender();
    int id = button->objectName()[button->objectName().length() - 1].toLatin1() - 0x30;
    setCommand("Period", id);
}

void FormGeneralWaveform::onFinalChanged()
{
    QPushButton* button = (QPushButton*) sender();
    int id = button->objectName()[button->objectName().length() - 1].toLatin1() - 0x30;
    setCommand("Final", id);
}

void FormGeneralWaveform::onTopChanged()
{
    QPushButton* button = (QPushButton*) sender();
    int id = button->objectName()[button->objectName().length() - 1].toLatin1() - 0x30;
    setCommand("Top", id);
}

void FormGeneralWaveform::onPlotClicked()
{
    QPushButton* button = (QPushButton*) sender();
    int id = button->objectName()[button->objectName().length() - 1].toLatin1() - 0x30;
    if(this->group == "QF" || this->group == "QD") {
        for(int i = 1; i <= 16; i++) {
            Client::writePV(QString::asprintf("SRC%02d-PS-%s1:getWaveform%d.PROC", i, this->group.toStdString().c_str(), id), 1);
            Client::writePV(QString::asprintf("SRC%02d-PS-%s2:getWaveform%d.PROC", i, this->group.toStdString().c_str(), id), 1);
        }
    }
    else {
        Client::writePV(QString::asprintf("SR-PS-%s1:getWaveform%d.PROC", this->group.toStdString().c_str(), id), 1);
        Client::writePV(QString::asprintf("SR-PS-%s2:getWaveform%d.PROC", this->group.toStdString().c_str(), id), 1);
    }
}

void FormGeneralWaveform::onBrowseClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select Waveform", getenv("HOME"));
    if(fileName.isEmpty()) {
        QMessageBox::warning(this, "Warning", "No waveforms selected", QMessageBox::Ok);
        return;
    }

    QPushButton* button = (QPushButton*) sender();
    int id = button->objectName()[button->objectName().length() - 1].toLatin1() - 0x30;
    this->findChild<QLineEdit*>("txtFile_" + STRING(id))->setText(fileName);
}

void FormGeneralWaveform::onUploadClicked()
{
    QPushButton* button = (QPushButton*) sender();
    int id = button->objectName()[button->objectName().length() - 1].toLatin1() - 0x30;
    QString pvName;
    QString fileName = this->findChild<QLineEdit*>("txtFile_" + STRING(id))->text();
    if(fileName.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Select waveform first");
        return;
    }

    float waveform[WAVEFORM_SIZE];
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

    if(this->group == "QF" || this->group == "QD") {
        for(int i = 1; i <= 16; i++) {
            Client::writeArray(QString::asprintf("SRC%02d-PS-%s1:getWaveform%d.PROC", i, this->group.toStdString().c_str(), id), waveform, WAVEFORM_SIZE);
            Client::writeArray(QString::asprintf("SRC%02d-PS-%s2:getWaveform%d.PROC", i, this->group.toStdString().c_str(), id), waveform, WAVEFORM_SIZE);
        }
    }
    else {
        Client::writeArray(QString::asprintf("SR-PS-%s1:getWaveform%d.PROC", this->group.toStdString().c_str(), id), waveform, WAVEFORM_SIZE);
        Client::writeArray(QString::asprintf("SR-PS-%s2:getWaveform%d.PROC", this->group.toStdString().c_str(), id), waveform, WAVEFORM_SIZE);
    }

    _file.close();
}
