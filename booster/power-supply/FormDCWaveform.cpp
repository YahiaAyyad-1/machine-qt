#include "FormDCWaveform.h"
#include "ui_FormDCWaveform.h"

FormDCWaveform::FormDCWaveform(QString device, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormDCWaveform)
{
    ui->setupUi(this);
    this->device = device;
    this->setWindowTitle(this->device + " Waveforms");

    QString hostname = "BO-PS-" + this->device;
    QHostInfo info = QHostInfo::fromName(hostname);
    this->ui->lblDevice->setText(hostname);
    this->ui->lblIP->setText(info.addresses()[0].toString());

    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
}

FormDCWaveform::~FormDCWaveform()
{
    delete ui;
}

void FormDCWaveform::on_btnSelectFile_clicked()
{
    QFileDialog di;
    di.setFileMode(QFileDialog::ExistingFile);
    di.setNameFilter(tr("Waveform Files (*.txt)"));
    di.setViewMode(QFileDialog::Detail);
    if(di.exec())
        this->ui->txtWaveformFile->setText(di.selectedFiles()[0]);
}

void FormDCWaveform::on_btnDownload_clicked()
{
    QFile waveform(this->ui->txtWaveformFile->text());
    QString file = QFile(this->ui->txtWaveformFile->text()).fileName();
    if(file.isEmpty())
    {
        QMessageBox::critical(this, "Error", "Empty file name");
        return;
    }

    QStringList fileName = file.split("-");
    if(fileName.size() != 2 || !fileName[1].startsWith("step") || fileName[1].size() <= 4)
    {
        QMessageBox::critical(this, "Error", "Invalid waveform file name: " + file);
        return;
    }

    QString name = fileName[1].split(".")[0];
    int step = QStringRef(&name, 4, name.size() - 4).toInt();
    Client::writePV(this->ui->lblDevice->text() + ":setWaveformStep", step);

    struct sockaddr_in device;
    char buffer[100];
    size_t bytes = 0;
    int socketFD = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(socketFD == -1)
    {
        QMessageBox::critical(this, "Error", "Could not create socket to device " + this->device);
        return;
    }

    memset(&device, 0, sizeof(device));
    device.sin_family = AF_INET;
    device.sin_port = htons(PORT);
    inet_pton(AF_INET, this->ui->lblIP->text().toStdString().c_str(), &device.sin_addr);

    int connected = ::connect(socketFD, (struct sockaddr*) &device, sizeof(device));
    if(connected == -1)
    {
        QMessageBox::critical(this, "Error", "Unable to connect to device " + this->device);
        SHUTDOW_AND_EXIT
    }

    bytes = write(socketFD, CANCEL_COMMAND, strlen(CANCEL_COMMAND));
    if(bytes != strlen(CANCEL_COMMAND))
    {
        QMessageBox::critical(this, "Error", "Error sending cancel command to device " + this->device);
        SHUTDOW_AND_EXIT
    }

    bytes = read(socketFD, buffer, sizeof(buffer));
    buffer[bytes] = '\0';
    if(bytes != strlen(buffer))
    {
        QMessageBox::critical(this, "Error", "Error reading from device " + this->device);
        SHUTDOW_AND_EXIT
    }

    if(strncmp(buffer, CANCEL_CODE, strlen(CANCEL_CODE)) != 0)
    {
        QMessageBox::critical(this, "Error", "Could not cancel previous operation for device " + this->device);
        SHUTDOW_AND_EXIT
    }

    if(!waveform.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QMessageBox::critical(this, "Error", "Could not open waveform file: " + waveform.fileName());
        SHUTDOW_AND_EXIT
    }

    QString waveformData = "";
    while(!waveform.atEnd())
        waveformData += waveform.readLine().replace("\n", "\r\n");

    waveformData = "d0\r\n" + waveformData + "\r\n;\r\n";
    waveform.close();

    bytes = write(socketFD, waveformData.toStdString().c_str(), strlen(waveformData.toStdString().c_str()));
    if(bytes != strlen(waveformData.toStdString().c_str()))
    {
        QMessageBox::critical(this, "Error", "Error writing waveform from file " + waveform.fileName());
        SHUTDOW_AND_EXIT
    }

    bytes = read(socketFD, buffer, sizeof(buffer));
    buffer[bytes] = '\0';

    shutdown(socketFD, SHUT_RDWR);
    ::close(socketFD);

    QString cmd = QString("(echo U0 ; sleep 10) | nc %1 3702 > /tmp/waveform.txt").arg(this->ui->lblIP->text());
    system( cmd.toStdString().c_str() );
    system( "sed -i '$d' /tmp/waveform.txt" );
    system( "sed -i 's/ //g' /tmp/waveform.txt" );

    QFile file1(this->ui->txtWaveformFile->text());
    QFile file2("/tmp/waveform.txt");
    if(file1.open(QIODevice::ReadOnly | QIODevice::Text) && file2.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QCryptographicHash hash1(QCryptographicHash::Md5);
        QCryptographicHash hash2(QCryptographicHash::Md5);
        if(hash1.addData(&file1) && hash2.addData(&file2))
        {
            if(hash1.result() == hash2.result())
                QMessageBox::information(this, "Information", "Waveform download successful");
            else
                QMessageBox::critical(this, "Information", "Waveform download failed!");
        }
        else
            QMessageBox::critical(this, "Information", "File verification failed!");
    }
    else
        QMessageBox::critical(this, "Information", "File open failed!");

    return;
}
