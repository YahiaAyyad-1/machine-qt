#include "scopes_window.h"
#include "ui_scopes_window.h"

ScopesWindow::ScopesWindow(QString title, QStringList channels, QStringList aliases, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ScopesWindow)
{
    ui->setupUi(this);

    this->setWindowTitle(title);
    ui->title->setText(title);
    ui->scope->setDataPVA(channels.size() >= 1 ? channels[0] : "");
    ui->scope->setDataPVB(channels.size() >= 2 ? channels[1] : "");
    ui->scope->setDataPVC(channels.size() >= 3 ? channels[2] : "");
    ui->scope->setDataPVD(channels.size() >= 4 ? channels[3] : "");
    ui->scope->setSizePVA(channels.size() >= 1 ? channels[0] + ".NORD" : "");
    ui->scope->setSizePVB(channels.size() >= 2 ? channels[1] + ".NORD" : "");
    ui->scope->setSizePVC(channels.size() >= 3 ? channels[2] + ".NORD" : "");
    ui->scope->setSizePVD(channels.size() >= 4 ? channels[3] + ".NORD" : "");
    ui->scope->setAliasA(aliases.size() >= 1 ? aliases[0] : "");
    ui->scope->setAliasB(aliases.size() >= 2 ? aliases[1] : "");
    ui->scope->setAliasC(aliases.size() >= 3 ? aliases[2] : "");
    ui->scope->setAliasD(aliases.size() >= 4 ? aliases[3] : "");
}

ScopesWindow::~ScopesWindow()
{
    delete ui;
}
