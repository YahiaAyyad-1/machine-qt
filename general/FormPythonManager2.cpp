#include "FormPythonManager2.h"
#include "ui_FormPythonManager2.h"

FormPythonManager2::FormPythonManager2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormPythonManager2)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    on_start = true;
    connect(&networkManager, &QNetworkAccessManager::finished, this, &FormPythonManager2::onRequestFinished);
    getAllProcessInfo("10.1.100.46");

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]{ getAllProcessInfo("10.1.100.46"); });
    timer->start(2000);


}
void FormPythonManager2::sendRequest(const QString &url, const QString &xmlRequest)
{
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "text/xml");

    QNetworkReply *reply = networkManager.post(request, xmlRequest.toUtf8());
    Q_UNUSED(reply);
//    connect(reply, &QNetworkReply::errorOccurred, this, &FormPythonManager2::onError);
}

void FormPythonManager2::onRequestFinished(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        parseResponse(responseData);
    }
    reply->deleteLater();
}

void FormPythonManager2::onError(QNetworkReply::NetworkError error) {
    Q_UNUSED(error);
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    reply->deleteLater();
}

void FormPythonManager2::parseResponse(const QByteArray &data)
{
    QString name, statename;
    QString server = "46";

       QXmlStreamReader xml(data);

       while (!xml.atEnd() && !xml.hasError()) {
           QXmlStreamReader::TokenType token = xml.readNext();
           if (token == QXmlStreamReader::StartElement && xml.name() == "struct") {
               while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "struct")) {
                   if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == "member") {
                       QString memberName, memberValue;
                       while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "member")) {
                           xml.readNext();
                           if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == "name") {
                               xml.readNext(); // Move to the value of the name
                               memberName = xml.text().toString();
                           } else if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == "string") {
                               xml.readNext(); // Move to the value of the string
                               memberValue = xml.text().toString();
                           }
                       }
                       if (memberName == "name") {
                           name = memberValue;
                       } else if (memberName == "statename") {
                           statename = memberValue;
                           if (on_start)
                           {
                               this->ui->ltService->addWidget(new PythonServiceWidget(name, statename, server, this));
                           }
                           else
                           {
                               QList<PythonServiceWidget*> widgets = this->ui->centralwidget->findChildren<PythonServiceWidget*>();
                               QList<PythonServiceWidget*>::iterator it = std::find_if(widgets.begin(), widgets.end(), [&](PythonServiceWidget* widget) {
                                       return widget->findChild<QLabel*>("lblSrvName")->text() == name;
                                   }
                               );
                               if (it != widgets.end()) {
                                   PythonServiceWidget* w = *it;
                                   QLabel* lblSrvStatus = w->findChild<QLabel*>("lblSrvStatus");
                                   if (lblSrvStatus->text() != statename)
                                   {
                                       lblSrvStatus->setText(statename);
                                       emit(w->statusChanged());
                                   }
                               } else {
                                   QMessageBox::warning(this, "Warning", "Service Not Found!");
                               }
                           }
                       }
                   }

                   xml.readNext();
               }
           }

       }
       if (on_start)
       {
           assignOnClick();
       }
       on_start = false;

}


void FormPythonManager2::assignOnClick()
{
    QVBoxLayout* buttonLayout = ui->ltService;

    // Iterate over all widgets in the layout
        for (int i = 0; i < buttonLayout->count(); ++i) {
            // Get the widget at index i
            QWidget *widget = buttonLayout->itemAt(i)->widget();

            // Check if the widget is a QWidget
            QWidget *containerWidget = qobject_cast<QWidget*>(widget);
            if (!containerWidget)
                continue; // Skip if it's not a QWidget

            // Find all child widgets of type QPushButton
            QList<QPushButton*> buttons = containerWidget->findChildren<QPushButton*>();
            foreach(QPushButton *button, buttons) {
                // Extract the service ID from the button's object name
                QString buttonID = button->objectName().replace("btnRestart", "");

                // Connect the clicked() signal of the button to the restartProcess() function
                connect(button, &QPushButton::clicked, this, [this, buttonID]() {
                    restartProcess(buttonID);
                });
            }
        }
}
void FormPythonManager2::getAllProcessInfo(const QString ip)
{
    sendRequest("http://"+ip+":9001/RPC2", "<methodCall><methodName>supervisor.getAllProcessInfo</methodName></methodCall>");
}

void FormPythonManager2::startProcess(const QString ip, const QString &service)
{
    QString request = QString("<methodCall><methodName>supervisor.startProcess</methodName><params><param><value><string>%1</string></value></param></params></methodCall>").arg(service);
    sendRequest("http://"+ip+":9001/RPC2", request);
}

void FormPythonManager2::stopProcess(const QString ip, const QString &service)
{
    QString request = QString("<methodCall><methodName>supervisor.stopProcess</methodName><params><param><value><string>%1</string></value></param></params></methodCall>").arg(service);
    sendRequest("http://"+ip+":9001/RPC2", request);
}


void FormPythonManager2::restartProcess(const QString &service)
{
    QMessageBox::StandardButton reply = QMessageBox::question(nullptr, "Confirmation", "Are you sure you want to restart " + service + " python script?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        QTimer *timer = new QTimer(this);

        // Set a single-shot timer with the desired interval (in milliseconds)
        int delayMilliseconds = 1000; // 1 second delay
        timer->setSingleShot(true);
        timer->start(delayMilliseconds);

        // Connect the timeout() signal of the timer to a lambda function
        connect(timer, &QTimer::timeout, this, [this, service]() {
            // This code will be executed after the delay
            startProcess("10.1.100.46", service);
        });

        stopProcess("10.1.100.46", service);
    }
}


FormPythonManager2::~FormPythonManager2()
{
    delete ui;
}
