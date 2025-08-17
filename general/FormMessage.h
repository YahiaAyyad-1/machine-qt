#ifndef FORMMESSAGE_H
#define FORMMESSAGE_H

#include <QMainWindow>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkInterface>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

#include "client.h"

namespace Ui {
class FormMessage;
}

class FormMessage : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormMessage(QWidget *parent = nullptr);
    ~FormMessage();

private slots:
    void on_btnSet_clicked();

    void on_btnBeamReady_clicked();

    void on_btnInjectionLate_clicked();

    void on_btnBeamDelivery_clicked();

    void on_btnInjectionProgress_clicked();

    void on_btnMachineMaintenance_clicked();

    void on_btnSetOperators_clicked();

    void on_btnRemoveOperators_clicked();

private:
    Ui::FormMessage *ui;
    QNetworkAccessManager *manager;
};

#endif // FORMMESSAGE_H
