#include "FormMachineManager.h"
#include "ui_FormMachineManager.h"

FormMachineManager::FormMachineManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormMachineManager)
{
    ui->setupUi(this);
    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
//    foreach (QPushButton* button, this->findChildren<QPushButton*>(QRegExp("btnDetails_*", Qt::CaseSensitive, QRegExp::Wildcard))) {
//        QObject::connect(button, SIGNAL(clicked(bool)), this, SLOT(detailsButtonsClicked()));
//    }

//    this->names.push_back("IOC-VA-IN");
//    this->names.push_back("IOC-VA-SR");
//    this->names.push_back("IOC-PS-IN");
//    this->names.push_back("IOC-PS-SR");
//    this->names.push_back("IOC-PS-ID09");
//    this->names.push_back("IOC-RF");
//    this->names.push_back("IOC-DI");
//    this->names.push_back("IOC-CAMS");
//    this->names.push_back("IOC-TI");
//    this->names.push_back("IOC-PSS");
//    this->names.push_back("IOC-PLC-IN");
//    this->names.push_back("IOC-PLC-SR");
//    this->names.push_back("IOC-PLC-ID09");
//    this->names.push_back("SEQ-DI");
//    this->names.push_back("SEQ-PS");
//    this->names.push_back("SEQ-MACHINE");
//    this->names.push_back("IOC-MO");
//    this->names.push_back("IOC-SSA");
//    this->names.push_back("IOC-AFG");
//    this->names.push_back("IOC-TCB");
//    this->names.push_back("IOC-FHT6020");
//    this->names.push_back("SEQ-RF");

    QFile file(":/configurations/ioc-manager.txt", this);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Warning", "Could not open IOCs manager prefixes list.", QMessageBox::Ok);
        return;
    }

    QString line;
    QTextStream stream(&file);
    while(!stream.atEnd()) {
        line = stream.readLine();
        ui->layout->addWidget(new IOCManagerWidget(line, this));
    }
}

FormMachineManager::~FormMachineManager()
{
    delete ui;
}

void FormMachineManager::detailsButtonsClicked()
{
//    QPushButton* button = (QPushButton*) sender();
//    int index = button->objectName().split("_")[1].toInt();
//    QString name = this->names[index];

//    this->stats = new FormIOCStats(name);
//    showUI(stats);
}

void FormMachineManager::on_pushButton_clicked()
{
//	Client::writePV("IOC-VA-IN:SysReset.PROC", 1U);
//	Client::writePV("IOC-VA-SR:SysReset.PROC", 1U);
//	Client::writePV("IOC-PS-IN:SysReset.PROC", 1U);
//	Client::writePV("IOC-PS-SR:SysReset.PROC", 1U);
//	Client::writePV("IOC-PS-ID09:SysReset.PROC", 1U);
//	Client::writePV("IOC-RF:SysReset.PROC", 1U);
//    // Client::writePV("IOC-DI:SysReset.PROC", 1U);
//	Client::writePV("IOC-CAMS:SysReset.PROC", 1U);
//	Client::writePV("IOC-TI:SysReset.PROC", 1U);
//	Client::writePV("IOC-PSS:SysReset.PROC", 1U);
//	Client::writePV("IOC-PLC-IN:SysReset.PROC", 1U);
//	Client::writePV("IOC-PLC-SR:SysReset.PROC", 1U);
//	Client::writePV("IOC-PLC-ID09:SysReset.PROC", 1U);
//	Client::writePV("SEQ-DI:SysReset.PROC", 1U);
//	Client::writePV("SEQ-PS:SysReset.PROC", 1U);
//	Client::writePV("SEQ-MACHINE:SysReset.PROC", 1U);
//	Client::writePV("IOC-MO:SysReset.PROC", 1U);
//	Client::writePV("IOC-SSA:SysReset.PROC", 1U);
//	Client::writePV("IOC-AFG:SysReset.PROC", 1U);
//	Client::writePV("IOC-TCB:SysReset.PROC", 1U);
//	Client::writePV("IOC-FHT6020:SysReset.PROC", 1U);
//	Client::writePV("SEQ-RF:SysReset.PROC", 1U);
}
