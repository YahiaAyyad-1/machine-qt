#include "FormRFCooling.h"
#include "ui_FormRFCooling.h"

FormRFCooling::FormRFCooling(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormRFCooling)
{
    ui->setupUi(this);
    QObject::connect(ui->btnClose, SIGNAL(clicked()), this, SLOT(close()));

    QString name;
    QString prefix;
    QString line;
    QFile _file;
    QTextStream config;

    _file.setFileName(":/configurations/rf-thermocouples.txt");
    if(!_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Could not open THC config file.", QMessageBox::Ok);
        return;
    }

    config.setDevice(&_file);
    while(!config.atEnd()) {
        line   = config.readLine();
        ui->ltThc->addWidget(new ThermocoupleWidget(line, line, this));
    }

}

FormRFCooling::~FormRFCooling()
{
    delete ui;
}

void FormRFCooling::on_btnRfThermocouplesReset_clicked()
{
    Client::writePV("SR-RF-THC:resetInterlock", 1);
    Client::writePV("SRC3-CO-HAB:resetInterlock", 1);
}
