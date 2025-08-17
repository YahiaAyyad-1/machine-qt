#include "FormMessage.h"
#include "ui_FormMessage.h"

FormMessage::FormMessage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormMessage)
{
    ui->setupUi(this);
    QObject::connect(ui->btnClose, SIGNAL(clicked()), this, SLOT(close()));

}

FormMessage::~FormMessage()
{
    delete ui;
}

void FormMessage::on_btnSet_clicked()
{
    QDateTime now;
    QString message;

    if(ui->txtMessage->text().isEmpty()) {
        QMessageBox::information(this, "Error", "Enter your message first.", QMessageBox::Ok);
        return;
    }

    now = QDateTime::currentDateTime();
    message = now.toString("[dd.MM.yyyy hh:mm AP] ");
    QString value = message + ui->txtMessage->text();
    Client::writeArray("message", (void*) value.toStdString().c_str(), value.length(), DBF_CHAR);
}

void FormMessage::on_btnBeamReady_clicked()
{
    QDateTime now;
    QString message;
    now = QDateTime::currentDateTime();
    message = now.toString("[dd.MM.yyyy hh:mm AP] ");
    QString value = message + "Beam is ready for users";
    Client::writeArray("message", (void*) value.toStdString().c_str(), value.length(), DBF_CHAR);
}



void FormMessage::on_btnInjectionLate_clicked()
{
     QDateTime now;
     QString message;
     now = QDateTime::currentDateTime();
     message = now.toString("[dd.MM.yyyy hh:mm AP] ");
     QString value = message + "Injection will be late due to some technical issues";
     Client::writeArray("message", (void*) value.toStdString().c_str(), value.length(), DBF_CHAR);

}

void FormMessage::on_btnBeamDelivery_clicked()
{
    QDateTime now;
    QString message;
    now = QDateTime::currentDateTime();
    message = now.toString("[dd.MM.yyyy hh:mm AP] ");
    QString value = message + "Beam delivery will be late due to some technical issues";
    Client::writeArray("message", (void*) value.toStdString().c_str(), value.length(), DBF_CHAR);
}

void FormMessage::on_btnInjectionProgress_clicked()
{
    QDateTime now;
    QString message;
    now = QDateTime::currentDateTime();
    message = now.toString("[dd.MM.yyyy hh:mm AP] ");
    QString value = message + "Injection to Storage-ring in progress";
    Client::writeArray("message", (void*) value.toStdString().c_str(), value.length(), DBF_CHAR);
}

void FormMessage::on_btnMachineMaintenance_clicked()
{
    QDateTime now;
    QString message;
    now = QDateTime::currentDateTime();
    message = now.toString("[dd.MM.yyyy hh:mm AP] ");
    QString value = message + "Machine under maintenance";
    Client::writeArray("message", (void*) value.toStdString().c_str(), value.length(), DBF_CHAR);
}

void FormMessage::on_btnSetOperators_clicked()
{
    QString ip = "";
    QStringList allowed_ip = {"10.2.0.41", "10.2.0.42", "10.2.0.68", "10.2.0.69", "10.1.22.199"};
    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();

        for (const QNetworkInterface &interface : interfaces) {
            // Check if the interface is up and running
            if (interface.flags() & QNetworkInterface::IsUp &&
                interface.flags() & QNetworkInterface::IsRunning &&
                !(interface.flags() & QNetworkInterface::IsLoopBack)) {

                // Iterate through all entries for this interface
                QList<QNetworkAddressEntry> entries = interface.addressEntries();
                for (const QNetworkAddressEntry &entry : entries) {
                    // Filter for IPv4 addresses
                    if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol) {
                        ip = entry.ip().toString();
                    }
                }
            }
        }

    this->manager = new QNetworkAccessManager(this);
    QNetworkRequest request(QUrl("http://10.1.100.46:8080/set_operators"));

    // Set request headers
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Create the JSON payload
    QJsonObject json;
    json["operator1"] = ui->lstOperator1->currentText();
    json["operator2"] = ui->lstOperator2->currentText();
    QJsonDocument jsonDoc(json);

    // Send the POST request
    if (allowed_ip.contains(ip)) {
        this->manager->post(request, jsonDoc.toJson());
    }


}

void FormMessage::on_btnRemoveOperators_clicked()
{
    QString ip = "";
    QStringList allowed_ip = {"10.2.0.41", "10.2.0.42", "10.2.0.68", "10.2.0.69", "10.1.22.199"};
    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();

        for (const QNetworkInterface &interface : interfaces) {
            // Check if the interface is up and running
            if (interface.flags() & QNetworkInterface::IsUp &&
                interface.flags() & QNetworkInterface::IsRunning &&
                !(interface.flags() & QNetworkInterface::IsLoopBack)) {

                // Iterate through all entries for this interface
                QList<QNetworkAddressEntry> entries = interface.addressEntries();
                for (const QNetworkAddressEntry &entry : entries) {
                    // Filter for IPv4 addresses
                    if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol) {
                        ip = entry.ip().toString();
                    }
                }
            }
        }

    this->manager = new QNetworkAccessManager(this);
    QNetworkRequest request(QUrl("http://10.1.100.46:8080/set_operators"));

    // Set request headers
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Create the JSON payload
    QJsonObject json;
    json["operator1"] = "---";
    json["operator2"] = "---";
    QJsonDocument jsonDoc(json);

    // Send the POST request
    if (allowed_ip.contains(ip)) {
        this->manager->post(request, jsonDoc.toJson());
    }
}
