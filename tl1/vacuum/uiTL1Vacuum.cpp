#include "uiTL1Vacuum.h"
#include "ui_uiTL1Vacuum.h"

uiTL1Vacuum::uiTL1Vacuum(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::uiTL1Vacuum)
{
    ui->setupUi(this);
    QObject::connect(ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));

    this->globalValves = NULL;
}

uiTL1Vacuum::~uiTL1Vacuum()
{
    delete ui;
}

void uiTL1Vacuum::on_pushButton_3_clicked()
{
    OPEN_UI(globalValves, ValvesWindow, this);
}
