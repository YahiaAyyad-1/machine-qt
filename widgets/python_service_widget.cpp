#include "python_service_widget.h"
#include "ui_python_service_widget.h"
#include <iostream>
PythonServiceWidget::PythonServiceWidget(QString srvName, QString srvStatus, QString server, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PythonServiceWidget)
{
    ui->setupUi(this);

    QObject::connect(this, SIGNAL(statusChanged()), this, SLOT(handle_status_changed()));

    ui->lblSrvName->setText(srvName);
    ui->lblSrvStatus->setText(srvStatus);
    if (server=="46")
    {
        ui->btnRestartSrv->setObjectName("btnRestart"+srvName);
    }
    emit(statusChanged());

    this->srvName = srvName;
    this->pythonServer = server;
}

PythonServiceWidget::~PythonServiceWidget()
{
    delete ui;
}

void PythonServiceWidget::on_btnRestartSrv_clicked()
{
    QString service = this->ui->lblSrvName->text();
    if (this->pythonServer == "202")
    {
    QMessageBox::StandardButton reply = QMessageBox::question(nullptr, "Confirmation", "Are you sure you want to restart " + service + " python script?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        this->ui->lblSrvStatus->setText("RESTARTING...");
        emit(statusChanged());
        QProcess* process = new QProcess;
        QStringList params;
        params << "-restart" << this->srvName;
        process->start("/home/control/qt-client/scripts/python_manager.py", params);
    }
    }

}

void PythonServiceWidget::handle_status_changed()
{
    QString status = ui->lblSrvStatus->text();
    if(status == "RUNNING")
    {
        ui->lblSrvStatus->setStyleSheet("color: green;");
    } else if (status == "STOPPED")
    {
        ui->lblSrvStatus->setStyleSheet("color: red;");
    } else
    {
        ui->lblSrvStatus->setStyleSheet("color: black;");
    }
}
