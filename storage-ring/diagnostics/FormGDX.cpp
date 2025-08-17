#include "FormGDX.h"
#include "ui_FormGDX.h"

#include <QIntValidator>

FormGDX::FormGDX(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormGDX)
{
    ui->setupUi(this);
    CONNECT_CLOSE_BUTTON;
    ui->txtSize->setValidator(new QIntValidator(0, 65, this));
}

FormGDX::~FormGDX()
{
    delete ui;
}

void FormGDX::on_pushButton_clicked()
{
    for(int i = 1; i <= 12; i++)
    {
        if(i == 3 || i == 4 || i == 9 || i == 10)
            continue;

        Client::writePV(QString::asprintf("libera%d:gdx:grouping:sfp:status3:clear", i), 0);
    }
}

void FormGDX::on_pushButton_2_clicked()
{
    for(int i = 1; i <= 12; i++)
    {
        if(i == 3 || i == 4 || i == 9 || i == 10)
            continue;

        Client::writePV(QString::asprintf("libera%d:gdx:grouping:sfp:status4:clear", i), 0);
    }
}

void FormGDX::on_pushButton_3_clicked()
{
    for(int i = 1; i <= 12; i++)
    {
        if(i == 3 || i == 4 || i == 9 || i == 10)
            continue;

        Client::writePV(QString::asprintf("libera%d:gdx:group_size_sp", ui->txtSize->text().toInt()), 0);
    }
}
