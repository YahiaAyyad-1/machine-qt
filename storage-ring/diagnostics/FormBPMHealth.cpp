#include "FormBPMHealth.h"
#include "ui_FormBPMHealth.h"

FormBPMHealth::FormBPMHealth(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormBPMHealth)
{
    ui->setupUi(this);
    CONNECT_CLOSE_BUTTON;

    this->timer = new QTimer(this);
    this->timer->setInterval(2000);
    QObject::connect(this->timer, &QTimer::timeout, this, &FormBPMHealth::onHealthCheckTimerUpdate);
    this->timer->start();
}

FormBPMHealth::~FormBPMHealth()
{
    delete ui;
}

void FormBPMHealth::onHealthCheckTimerUpdate()
{
    QStringList items;
    QString unit;
    int value;
    int minor;
    int major;
    for (QELabel* label : this->findChildren<QELabel*>()) {
        if (label->text() == "N/A")
            continue;

        items = label->text().split(' ');
        unit  = items[1];
        value = items[0].toInt();
        if (unit == "degC") {
            minor = 65;
            major = 75;
        }
        else {
            minor = 6300;
            major = 6500;
        }

        if (value < minor)
            label->setDefaultStyle("QWidget { background-color: #e0dcda; color: #000000; }");
        else if (value >= minor && value < major)
            label->setDefaultStyle("background-color: yellow; color: #000000;");
        else
            label->setDefaultStyle("background-color: red; color: #000000;");
    }
}
