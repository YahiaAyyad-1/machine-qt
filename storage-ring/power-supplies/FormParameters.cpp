#include "FormParameters.h"
#include "ui_FormParameters.h"

FormParameters::FormParameters(QString group, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormParameters)
{
    ui->setupUi(this);
    this->group = group;
    this->setWindowTitle(this->group + " Parameters");
    this->pvParameters = new QEpicsPV(this->group + ":getParameters");
    this->ui->btnLoadFlash->setVariableNameSubstitutionsProperty("group=" + this->group);
    this->ui->btnReset->setVariableNameSubstitutionsProperty("group=" + this->group);
    this->ui->btnReset_2->setVariableNameSubstitutionsProperty("group=" + this->group);
    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
    QObject::connect(this->pvParameters, SIGNAL(valueChanged(QVariant)), this, SLOT(onParametersChanged(QVariant)));

    Client::writePV(this->group + ":getParameters.PROC", 1);
    QFile _config(":/configurations/sr-ps-parameters.txt");
    if(!_config.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Could not load parameters definitions.");
    }
    else {
        QString line;
        QStringList items;
        QTextStream parametersList(&_config);
        while(!parametersList.atEnd()) {
            line = parametersList.readLine();
            items = line.split(',');
            this->parameters.push_back({items[2], items[1], items[0].toInt(Q_NULLPTR, 16)});
        }
    }
}

FormParameters::~FormParameters()
{
    delete ui;
}

void FormParameters::onParametersChanged(QVariant value)
{
    QStringList values = value.toStringList();
    for(int i = 0; i < this->parameters.size(); i++)
    {
        raw32_t raw_value;
        QString v = values[this->parameters[i].index];
        if(this->parameters[i].type == "f")
        {
            raw_value.i_val = v.toUInt();
            this->findChild<QLabel*>("lbl_" + this->parameters[i].name)->setText(QString::number(raw_value.f_val));
            this->findChild<QLineEdit*>("txt_" + this->parameters[i].name)->setText(QString::number(raw_value.f_val));
        }
        else if(this->parameters[i].type == "i")
        {
            this->findChild<QLabel*>("lbl_" + this->parameters[i].name)->setText(v);
            this->findChild<QLineEdit*>("txt_" + this->parameters[i].name)->setText(v);
        }
        else if(this->parameters[i].type == "h")
        {
            this->findChild<QLabel*>("lbl_" + this->parameters[i].name)->setText("0x" + QString::number(v.toUInt(), 16));
            this->findChild<QLineEdit*>("txt_" + this->parameters[i].name)->setText("0x" + QString::number(v.toUInt(), 16));
        }
    }
}

void FormParameters::on_btnBrowse_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Select parameters file", QString(getenv("HOME")), tr("Parameter files (*.pf)"));
    if(!fileName.isEmpty())
        this->ui->txtFile->setText(fileName + (fileName.endsWith(".pf") ? "" : ".pf"));
    else
        QMessageBox::information(this, "No file selected", "No parameter file was selected.");
}

void FormParameters::on_btnSave_clicked()
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
    for(int i = 0; i < this->parameters.length(); i++)
    {
        stream << this->parameters[i].name << "=" << this->findChild<QLineEdit*>("txt_" + this->parameters[i].name)->text() << "\n";
    }

    pf.close();
    QMessageBox::information(this, "File saved", "Parameters saved to file " + pf.fileName());
}

void FormParameters::on_btnLoad_clicked()
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

void FormParameters::on_btnUpload_clicked()
{
    uint32_t values[256] = {0};
    for(int i = 0; i < this->parameters.size(); i++)
    {
        QString name = this->parameters[i].name;
        QString type = this->parameters[i].type;
        int index = this->parameters[i].index;
        QString v = this->findChild<QLineEdit*>("txt_" + name)->text();
        if(type == "f")
        {
            float x = v.toFloat();
            uint32_t iv = 0U;
            memcpy(&iv, &x, sizeof(x));
            values[index] = iv;
        }
        else if(type == "i")
            values[index] = v.toUInt();
        else if(type == "h")
            values[index] = v.toUInt(nullptr, 16);
    }

    Client::writeArray(this->group + ":setParameters", values, 256);
    Client::writePV(this->group + ":getParameters.PROC", 1);
}

void FormParameters::on_btnBrowse2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select firmware file", QString(getenv("HOME")), tr("Firmware file (*.css)"));
    if(!fileName.isEmpty())
        this->ui->txtFirmwareFile->setText(fileName);
    else
        QMessageBox::information(this, "No file selected", "No firmware file was selected.");
}

void FormParameters::on_btnUpdateFW_clicked()
{
    if(this->ui->txtFirmwareFile->text().isEmpty())
        return;

    QFile fw(this->ui->txtFirmwareFile->text());
    if(!fw.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this, "Error", "Could not open firmware file: " + fw.fileName());
        return;
    }

    if(fw.bytesAvailable() != FIRMWARE_SIZE)
    {
        QMessageBox::critical(this, "Error", "Firmware file not valid. Size should be 131072 bytes.");
        return;
    }

    uint32_t firmware[32768] = {0};
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

    Client::writeArray(this->group + ":setFirmware", firmware, 32768);
}
