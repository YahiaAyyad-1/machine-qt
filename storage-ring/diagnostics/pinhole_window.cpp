#include "pinhole_window.h"
#include "ui_pinhole_window.h"

PinholeWindow::PinholeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PinholeWindow)
{
    ui->setupUi(this);
    CONNECT_CLOSE_BUTTON;
}

PinholeWindow::~PinholeWindow()
{
    delete ui;
}

void PinholeWindow::on_btnGUI_clicked()
{
    QFile::copy(":/scripts/run-ad-cam", "/tmp/run-ad-cam");
    QProcess* p = new QProcess(this);
    // p->start("bash /tmp/run-ad-cam SRC16-DI-PNHL CAM");
    p->start("/bin/bash", {"/tmp/run-ad-cam", "SRC16-DI-PNHL", "CAM"});
}

void PinholeWindow::on_btnImageJ_clicked()
{
    QFile::copy(":/scripts/run-ad-viewer", "/tmp/run-ad-viewer");
    QProcess* p = new QProcess(this);
    p = new QProcess(this);
    // p->start("bash /tmp/run-ad-viewer SRC16-DI-PNHL CAM");
    p->start("/bin/bash", {"/tmp/run-ad-viewer", "SRC16-DI-PNHL", "CAM"});
}
