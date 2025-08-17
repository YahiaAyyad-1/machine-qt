#include "FormPythonManager.h"
#include "ui_FormPythonManager.h"

FormPythonManager::FormPythonManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormPythonManager)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    FormPythonManager::pythonManagerOpened = true;

    this->update(true);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]{ update(false); });
    timer->start(2000);
}

void FormPythonManager::update(bool init)
{
    QProcess* process = new QProcess();
    QStringList params;
    params << "-getData";
    process->start("/home/control/qt-client/scripts/python_manager.py", params);
    process->waitForFinished(-1);
    QByteArray p_stdout = process->readAll();
    QString p_stderr = process->readAllStandardError();
    if(!p_stderr.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Could not read Services!");
    } else
    {
        QString jsonString = QString::fromUtf8(p_stdout).replace('\'', '\"');
        QByteArray jsonData = jsonString.toUtf8();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
        if (!jsonDoc.isArray())
        {
            // Json data is not an array!
            QMessageBox::warning(this, "Warning", "Could not read Services!");
        }
        QJsonArray jsonArray = jsonDoc.array();
        for (const QJsonValue& value: jsonArray)
        {
            if (value.isObject())
            {
                QJsonObject jsonObj = value.toObject();
                QString name = jsonObj.value("name").toString();
                QString state = jsonObj.value("state").toString();
                QString server = "202";
                if (init)
                    this->ui->ltService->addWidget(new PythonServiceWidget(name, state, server, this));
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
                        if (lblSrvStatus->text() != state)
                        {
                            lblSrvStatus->setText(state);
                            emit(w->statusChanged());
                        }
                    } else {
                        QMessageBox::warning(this, "Warning", "Service Not Found!");
                    }
                }
            }
        }
    }
}

FormPythonManager::~FormPythonManager()
{
    FormPythonManager::pythonManagerOpened = false;
    delete ui;
}
