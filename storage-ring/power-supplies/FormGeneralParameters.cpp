#include "FormGeneralParameters.h"
#include "ui_FormGeneralParameters.h"

FormGeneralParameters::FormGeneralParameters(QString magnet, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormGeneralParameters)
{
    ui->setupUi(this);
    this->group = magnet;
    this->setWindowTitle(this->group + " Parameters");
    CONNECT_CLOSE_BUTTON;

    QFile _config(":/configurations/sr-ps-parameters.txt");
    if(!_config.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Could not load parameters definitions.");
    }

    QString line;
    QStringList items;
    QTextStream parametersList(&_config);
    while(!parametersList.atEnd()) {
        line = parametersList.readLine();
        items = line.split(',');
        this->parameters.push_back({items[2], items[1], items[0].toInt(Q_NULLPTR, 16)});
    }
}

FormGeneralParameters::~FormGeneralParameters()
{
    delete ui;
}

void FormGeneralParameters::on_btnBrowse_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select parameters file", getenv("HOME"), tr("Parameters (*.pf)"));
    if(fileName.isEmpty()) {
        QMessageBox::warning(this, "Error", "No parameters file selected", QMessageBox::Ok);
        return;
    }

    ui->txtFile->setText(fileName);
}

void FormGeneralParameters::on_btnBrowseFW_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select firmware file", getenv("HOME"), tr("Firmware (*.bin)"));
    if(fileName.isEmpty()) {
        QMessageBox::warning(this, "Error", "No firmware file selected", QMessageBox::Ok);
        return;
    }

    ui->txtFirmwareFile->setText(fileName);
}

void FormGeneralParameters::on_btnLoad_clicked()
{
    if(this->ui->txtFile->text().isEmpty())
        return;

    QFile pf(this->ui->txtFile->text());
    if(!pf.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::information(this, "Error open file.", "Could not open file " + pf.fileName());
        return;
    }

    QTextStream stream(&pf);
    while(!stream.atEnd())
    {
        QString line  = stream.readLine();
        QStringList list = line.split('=');
        QString name  = list[0];
        QString value = list[1];
        QLineEdit* txt = this->findChild<QLineEdit*>("txt_" + name);
        if(!txt)
        {
            QMessageBox::critical(this, "Error", "Parameter " + name + " not found.");
            return;
        }
        txt->setText(value);
    }

    pf.close();
    QMessageBox::information(this, "File saved", "Parameters loaded from file " + pf.fileName());
}

void FormGeneralParameters::on_btnSave_clicked()
{
    if(this->ui->txtFile->text().isEmpty())
        return;

    QFile pf(this->ui->txtFile->text());
    if(!pf.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::information(this, "Error open file.", "Could not open file " + pf.fileName());
        return;
    }

    QTextStream stream(&pf);
    QLineEdit* txt;
    for(int i = 0; i < this->parameters.length(); i++)
    {
        txt = this->findChild<QLineEdit*>("txt_" + this->parameters[i].name);
        if(!txt) {
            QMessageBox::warning(this, "Error", "Could not find parameter " + this->parameters[i].name);
            pf.close();
            return;
        }
        stream << this->parameters[i].name << "=" << txt->text() << "\n";
    }

    pf.close();
    QMessageBox::information(this, "File saved", "Parameters saved to file " + pf.fileName());
}

void FormGeneralParameters::on_btnUpdateFW_clicked()
{
    if(this->ui->txtFirmwareFile->text().isEmpty())
        return;

    QFile fw(this->ui->txtFirmwareFile->text());
    if(!fw.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Error", "Could not open firmware file: " + fw.fileName());
        return;
    }

    if(fw.bytesAvailable() != FIRMWARE_SIZE) {
        QMessageBox::critical(this, "Error", "Firmware file not valid. Size should be 131072 bytes.");
        return;
    }

    uint32_t firmware[FIRMWARE_ARRAY] = {0};
    int count = 0;
    while(fw.bytesAvailable() > 0)
    {
        QByteArray buffer = fw.read(4);
        QByteArray data;
        for(int i = 3; i >= 0; i--)
            data.append(buffer[i]);

        QDataStream ts(data);
        ts >> firmware[count];
        count++;
    }

    if(this->group == "QF" || this->group == "QD") {
        for(int i = 1; i <= 16; i++) {
            Client::writeArray(QString::asprintf("SRC%02d-PS-%s1:setFirmware", i, this->group.toStdString().c_str()), firmware, FIRMWARE_ARRAY);
            Client::writeArray(QString::asprintf("SRC%02d-PS-%s2:setFirmware", i, this->group.toStdString().c_str()), firmware, FIRMWARE_ARRAY);
        }
    }
    else {
        Client::writeArray(QString::asprintf("SR-PS-%s1:setFirmware", this->group.toStdString().c_str()), firmware, FIRMWARE_ARRAY);
        Client::writeArray(QString::asprintf("SR-PS-%s2:setFirmware", this->group.toStdString().c_str()), firmware, FIRMWARE_ARRAY);
    }

    // Client::writeArray(this->group + ":setFirmware", firmware, 32768);
}

void FormGeneralParameters::on_btnResetFW_clicked()
{
    if(this->group == "QF" || this->group == "QD") {
        for(int i = 1; i <= 16; i++) {
            Client::writePV(QString::asprintf("SRC%02d-PS-%s1:reset", i, this->group.toStdString().c_str()), 1);
            Client::writePV(QString::asprintf("SRC%02d-PS-%s2:reset", i, this->group.toStdString().c_str()), 1);
        }
    }
    else {
        Client::writePV(QString::asprintf("SR-PS-%s1:reset", this->group.toStdString().c_str()), 1);
        Client::writePV(QString::asprintf("SR-PS-%s2:reset", this->group.toStdString().c_str()), 1);
    }
}

void FormGeneralParameters::on_btnResetParameters_clicked()
{
    if(this->group == "QF" || this->group == "QD") {
        for(int i = 1; i <= 16; i++) {
            Client::writePV(QString::asprintf("SRC%02d-PS-%s1:reset", i, this->group.toStdString().c_str()), 0);
            Client::writePV(QString::asprintf("SRC%02d-PS-%s2:reset", i, this->group.toStdString().c_str()), 0);
        }
    }
    else {
        Client::writePV(QString::asprintf("SR-PS-%s1:reset", this->group.toStdString().c_str()), 0);
        Client::writePV(QString::asprintf("SR-PS-%s2:reset", this->group.toStdString().c_str()), 0);
    }
}

void FormGeneralParameters::on_btnUpdateParameters_clicked()
{
    uint32_t values[256] = {0};
    QLineEdit* txt;
    for(int i = 0; i < this->parameters.length(); i++)
    {
        QString name = this->parameters[i].name;
        QString type = this->parameters[i].type;
        int index = this->parameters[i].index;

        txt = this->findChild<QLineEdit*>("txt_" + name);
        if(!txt) {
            QMessageBox::warning(this, "Error", "Could not find parameter " + this->parameters[i].name);
            return;
        }
        QString v = txt->text();
        if(type == "float")
        {
            float x = v.toFloat();
            uint32_t iv = 0U;
            memcpy(&iv, &x, sizeof(x));
            values[index] = iv;
        }
        else if(type == "int")
            values[index] = v.toUInt();
        else if(type == "hex")
            values[index] = v.toUInt(nullptr, 16);
    }

    if(this->group == "QF" || this->group == "QD") {
        for(int i = 1; i <= 16; i++) {
            Client::writeArray(QString::asprintf("SRC%02d-PS-%s1:setParameters", i, this->group.toStdString().c_str()), values, 256);
            Client::writeArray(QString::asprintf("SRC%02d-PS-%s2:setParameters", i, this->group.toStdString().c_str()), values, 256);
        }
    }
    else {
        Client::writeArray(QString::asprintf("SR-PS-%s1:setParameters", this->group.toStdString().c_str()), values, 256);
        Client::writeArray(QString::asprintf("SR-PS-%s2:setParameters", this->group.toStdString().c_str()), values, 256);
    }

    QFile t("/home/control/p2.txt");
    t.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream st(&t);
    for(int i = 0; i < 256; i++)
        st << values[i] << "\n";

    t.close();
}
