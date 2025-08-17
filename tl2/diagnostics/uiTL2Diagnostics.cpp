#include "uiTL2Diagnostics.h"
#include "ui_uiTL2Diagnostics.h"
#include "QMessageBox"

uiTL2Diagnostics::uiTL2Diagnostics(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::uiTL2Diagnostics)
{
    ui->setupUi(this);
}

uiTL2Diagnostics::~uiTL2Diagnostics()
{
    delete ui;
}

void uiTL2Diagnostics::on_btnClose_clicked()
{
    close();
}

//void uiTL2Diagnostics::on_btnMoveCAM1In_clicked()
//{
//    Client::writePV("TL2-CAM1:setIn", "1");
//}

//void uiTL2Diagnostics::on_btnMoveCAM2In_clicked()
//{
//    Client::writePV("TL2-CAM2:setIn", "1");
//}

//void uiTL2Diagnostics::on_btnMoveCAM3In_clicked()
//{
//    Client::writePV("TL2-CAM3:setIn", "1");
//}

//void uiTL2Diagnostics::on_btnMoveCAM4In_clicked()
//{
//    Client::writePV("TL2-CAM4:setIn", "1");
//}

//void uiTL2Diagnostics::on_btnMoveCAM1Out_clicked()
//{
//    Client::writePV("TL2-CAM1:setOut", "1");
//}

//void uiTL2Diagnostics::on_btnMoveCAM4Out_clicked()
//{
//    Client::writePV("TL2-CAM4:setOut", "1");
//}

//void uiTL2Diagnostics::on_btnMoveCAM2Out_clicked()
//{
//    Client::writePV("TL2-CAM2:setOut", "1");
//}

//void uiTL2Diagnostics::on_btnMoveCAM3Out_clicked()
//{
//    Client::writePV("TL2-CAM3:setOut", "1");
//}

void uiTL2Diagnostics::on_btnScreensOut_clicked()
{
    Client::writePV("TL2-DI-FS1:setOut", "1");
    QThread::sleep(1);
    Client::writePV("TL2-DI-FS2:setOut", "1");
    QThread::sleep(1);
    Client::writePV("TL2-DI-FS3:setOut", "1");
    QThread::sleep(1);
    Client::writePV("TL2-DI-FS4:setOut", "1");
}
