#include "FormFastInterlock.h"
#include "ui_FormFastInterlock.h"

FormFastInterlock::FormFastInterlock(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormFastInterlock)
{
    ui->setupUi(this);
    CONNECT_CLOSE_BUTTON;
}

FormFastInterlock::~FormFastInterlock()
{
    delete ui;
}

void FormFastInterlock::on_btnReset_clicked()
{
    int l;
    int b;

    for(l = 1; l <= 12; l++) {
        for(b = 1; b <= 4; b++) {
            Client::writePV(QString::asprintf("libera%d:bpm%d:ilk:enabled_sp", l, b), 0);
            Client::writePV(QString::asprintf("libera%d:bpm%d:ilk:status:reset_sp", l, b), 0);
        }
    }
}
