#ifndef FORMPYTHONMANAGER_H
#define FORMPYTHONMANAGER_H

#include <QMainWindow>
#include <QLabel>
#include <QList>
#include <QProcess>
#include <QMessageBox>
#include <QTimer>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "widgets/python_service_widget.h"

namespace Ui {
class FormPythonManager;
}

class FormPythonManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormPythonManager(QWidget *parent = nullptr);
    ~FormPythonManager();

    static bool pythonManagerOpened;

private slots:
    void update(bool init);

private:
    Ui::FormPythonManager *ui;

};

#endif // FORMPYTHONMANAGER_H
