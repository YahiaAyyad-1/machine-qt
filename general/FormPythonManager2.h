#ifndef FORMPYTHONMANAGER2_H
#define FORMPYTHONMANAGER2_H

#include <QMainWindow>
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QXmlStreamReader>
#include <QTimer>
#include <QLabel>
#include <QPushButton>
#include <QList>
#include <QMessageBox>
#include "widgets/python_service_widget.h"
#include <iostream>

namespace Ui {
class FormPythonManager2;
}

class FormPythonManager2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormPythonManager2(QWidget *parent = nullptr);
    ~FormPythonManager2();

    void getAllProcessInfo(const QString ip);
    void startProcess(const QString ip, const QString &service);
    void stopProcess(const QString ip, const QString &service);
    void restartProcess(const QString &service);
    void assignOnClick();

private slots:
    void sendRequest(const QString &url, const QString &xmlRequest);
    void onRequestFinished(QNetworkReply *reply);
    void onError(QNetworkReply::NetworkError error);
    void parseResponse(const QByteArray &data);


private:
    Ui::FormPythonManager2 *ui;


    bool on_start;
    QNetworkAccessManager networkManager;

};

#endif // FORMPYTHONMANAGER2_H
