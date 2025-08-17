#include "uiBORFMain.h"
#include "ui_uiBORFMain.h"

#include <QProcess>

uiBORFMain::uiBORFMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::uiBORFMain)
{
    ui->setupUi(this);
    QObject::connect(ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
}

uiBORFMain::~uiBORFMain()
{
    delete ui;
}

void uiBORFMain::on_btnOpenLLE_clicked()
{
    QString input = "lle3-new";
    QProcess* process = new QProcess();
    process->start(input, {""});
}

void uiBORFMain::on_btnCavity_clicked()
{
    rfSp = new uiBORFSetpoints;
    rfSp->show();
}

void uiBORFMain::on_btnResetInterlocks_clicked()
{
    Client::writePV("BOC06-RF-CAV:resetInterlocks", 1);
    Client::writePV("BOC06-RF-CAV:resetTemperatureInterlock", 1);
}

void uiBORFMain::on_btnLoadProfile_clicked()
{
    int i = 0;
    bool ok;
    double data[512];
    double item;
    QString line;
    QFile file;
    QTextStream profile;

    file.setFileName(":/profiles/rf_profile.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Warning", "Could not open profile.", QMessageBox::Ok);
        return;
    }

    profile.setDevice(&file);
    while(!profile.atEnd()) {
        line = profile.readLine();
        item = line.toDouble(&ok);
        std::cout << item << std::endl;
        if(!ok) {
            QMessageBox::warning(this, "Warning", "Error parsing profile.", QMessageBox::Ok);
            file.close();
            return;
        }

        data[i++] = item;
    }

    Client::writeArray("LLE3:BRD1:RAMP:AMP", data, 512, DBF_DOUBLE);
    Client::writePV("LLE3:BRD1:RAMP:LOAD", 1);
}
