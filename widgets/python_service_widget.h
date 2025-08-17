#ifndef PYTHON_SERVICE_WIDGET_H
#define PYTHON_SERVICE_WIDGET_H

#include <QWidget>
#include <QProcess>
#include <QMessageBox>
#include "general/FormPythonManager2.h"

namespace Ui {
class PythonServiceWidget;
}

class PythonServiceWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PythonServiceWidget(QString srvName, QString srvStatus, QString server, QWidget *parent = nullptr);
    ~PythonServiceWidget();

signals:
    void statusChanged();

private slots:
    void on_btnRestartSrv_clicked();

    void handle_status_changed();

private:
    Ui::PythonServiceWidget *ui;

    QString srvName;
    QString pythonServer;
};

#endif // PYTHON_SERVICE_WIDGET_H
