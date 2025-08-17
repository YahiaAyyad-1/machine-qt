#include "FormTimer.h"
#include "ui_FormTimer.h"

FormTimer::FormTimer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormTimer)
{
    ui->setupUi(this);
    CONNECT_CLOSE_BUTTON;
}

FormTimer::~FormTimer()
{
    delete ui;
}

void FormTimer::on_btnExpert_clicked()
{

    QString goldenHash = "675eba8ed190a54e63361c44dac965fa2d70ddd45c6d3bfdc64c71f7c360df41";
    FormPassword *passwordWindow = new FormPassword(goldenHash, this);
    QObject::connect(passwordWindow, SIGNAL(authenticated()), this, SLOT(open_timers_expert()));

    if (!FormPassword::dialogOpen) {
        passwordWindow->show();
        FormPassword::dialogOpen = true;
    }

}

void FormTimer::open_timers_expert()
{
    FormTimerExpert* expert = new FormTimerExpert(this);
    expert->show();
}
