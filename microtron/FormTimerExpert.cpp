#include "FormTimerExpert.h"
#include "ui_FormTimerExpert.h"

FormTimerExpert::FormTimerExpert(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormTimerExpert)
{
    ui->setupUi(this);
    CONNECT_CLOSE_BUTTON;
}

FormTimerExpert::~FormTimerExpert()
{
    delete ui;
}

void FormTimerExpert::on_btnAgpsTSreset_clicked()
{
    Client::writePV("AGPS:reset_timers_both",1);
    Client::writePV("AGPS:timer_hours_trig_stand",0);
    Client::writePV("AGPS:timer_min_trig_stand",0);
}

void FormTimerExpert::on_btnAgpsTreset_clicked()
{
    Client::writePV("AGPS:reset_timers_trig",1);
    Client::writePV("AGPS:timer_hours_trig",0);
    Client::writePV("AGPS:timer_min_trig",0);
}

void FormTimerExpert::on_btncathTSreset_clicked()
{
    Client::writePV("AGPS:reset_timers_both_cathod",1);
    Client::writePV("AGPS:timer_hours_trig_stand_cathod",0);
    Client::writePV("AGPS:timer_min_trig_stand_cathod",0);
}

void FormTimerExpert::on_btncathTreset_clicked()
{
    Client::writePV("AGPS:reset_timers_trig_cathod",1);
    Client::writePV("AGPS:timer_hours_trig_cathod",0);
    Client::writePV("AGPS:timer_min_trig_cathod",0);
}
