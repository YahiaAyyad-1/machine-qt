#include "FormLiberaMain.h"
#include "ui_FormLiberaMain.h"

FormLiberaMain::FormLiberaMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormLiberaMain)
{
    ui->setupUi(this);
    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));

//    QPushButton* button;
//    QComboBox* combo;
//    for(int i = 1; i <= 6; i++)
//    {
//        button = this->findChild<QPushButton*>("btnHealth_" + QString::number(i));
//        QObject::connect(button, SIGNAL(clicked(bool)), this, SLOT(healthButton_Clicked()));

//        button = this->findChild<QPushButton*>("btnClock_" + QString::number(i));
//        QObject::connect(button, SIGNAL(clicked(bool)), this, SLOT(clockButton_Clicked()));

//        combo = this->findChild<QComboBox*>("cbModes_" + QString::number(i));
//        QObject::connect(combo, SIGNAL(currentIndexChanged(int)), this, SLOT(modesMenu_Clicked()));

//        button = this->findChild<QPushButton*>("btnConf_" + QString::number(i));
//        QObject::connect(button, SIGNAL(clicked(bool)), this, SLOT(configButton_Clicked()));
//    }
}

FormLiberaMain::~FormLiberaMain()
{
    delete ui;
}

//void FormLiberaMain::healthButton_Clicked()
//{
//    QPushButton* button = (QPushButton*) sender();
//    int index = button->objectName().split('_')[1].toInt();
//    this->health = new FormLiberaHealth(index);
//    this->health->show();
//}

//void FormLiberaMain::clockButton_Clicked()
//{
//    QPushButton* button = (QPushButton*) sender();
//    int index = button->objectName().split('_')[1].toInt();
//    this->clocks = new FormLiberaClock(index);
//    this->clocks->show();
//}

//void FormLiberaMain::modesMenu_Clicked()
//{
//    QComboBox* combo = (QComboBox*) sender();
//    int libera = combo->objectName().split('_')[1].toInt();
//    int index = combo->currentIndex();
//    switch(index)
//    {
//    case 0:
//        break;
//    case 1:
//        this->ft = new FormLiberaFirstTurn(libera);
//        this->ft->show();
//        break;
//    case 2:
//        this->fr = new FormLiberaFreeRun(libera);
//        this->fr->show();
//        break;
//    case 3:
//        this->tbt = new FormLiberaTurnByTurn();
//        this->tbt->show();
//        break;
//    case 4:
//        this->tt64 = new FormLiberaTT64(libera);
//        this->tt64->show();
//        break;
//    case 5:
//        this->tt1024 = new FormLiberaTT1024(libera);
//        this->tt1024->show();
//        break;
//    default:
//        break;
//    }

//    combo->setCurrentIndex(0);
//    return;
//}

//void FormLiberaMain::configButton_Clicked()
//{
//    QPushButton* button = (QPushButton*) sender();
//    int index = button->objectName().split('_')[1].toInt();
//    this->config = new FormLiberaConfiguration(index);
//    this->config->show();
//}

void FormLiberaMain::on_btnConfiguration_clicked()
{
    this->control = new FormLiberaControl;
    this->control->show();
}
