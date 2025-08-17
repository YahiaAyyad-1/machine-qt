#ifndef FORMDCWAVEFORM_H
#define FORMDCWAVEFORM_H

#include <QMainWindow>
#include <QFileDialog>
#include <QHostInfo>
#include <QMessageBox>
#include <QCryptographicHash>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "client.h"

#define SHUTDOW_AND_EXIT \
    shutdown(socketFD, SHUT_RDWR); \
    ::close(socketFD); \
    return;

#define PORT 3702
#define CANCEL_COMMAND "!\r\n"
#define CANCEL_CODE    "er01"

namespace Ui {
class FormDCWaveform;
}

class FormDCWaveform : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormDCWaveform(QString device, QWidget *parent = 0);
    ~FormDCWaveform();

private slots:
    void on_btnSelectFile_clicked();

    void on_btnDownload_clicked();

private:
    Ui::FormDCWaveform *ui;
    QString device;
};

#endif // FORMDCWAVEFORM_H
