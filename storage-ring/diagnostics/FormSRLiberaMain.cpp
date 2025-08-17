#include "FormSRLiberaMain.h"
#include "ui_FormSRLiberaMain.h"

FormSRLiberaMain::FormSRLiberaMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormSRLiberaMain)
{
    ui->setupUi(this);
    QObject::connect(ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));

    QEpicsPV* pv;
    for(int libera = 1; libera <= 12; libera++)
    {
        for(int bpm = 1; bpm <= 4; bpm++)
        {
            pvLedSync[bpm + 4 * (libera - 1) - 1] = new QEpicsPV(QString::asprintf("libera%d:bpm%d:sync_st_m", libera, bpm));
            QObject::connect(pvLedSync[bpm + 4 * (libera - 1) - 1], SIGNAL(valueChanged(QVariant)), this, SLOT(ledSyncStatus_Changed()));

            pv = new QEpicsPV(QString::asprintf("libera%d:bpm%d:sensors:temp_mon", libera, bpm));
            this->pvBPMTemps.push_back(pv);
        }

        pv = new QEpicsPV(QString::asprintf("libera%d:icb:sensors:temp_mon", libera));
        this->pvBPMTemps.push_back(pv);

        pv = new QEpicsPV(QString::asprintf("libera%d:gdx:sensors:temp_mon", libera));
        this->pvBPMTemps.push_back(pv);

        pv = new QEpicsPV(QString::asprintf("libera%d:evrx:sensors:temp_mon", libera));
        this->pvBPMTemps.push_back(pv);

        pv = new QEpicsPV(QString::asprintf("libera%d:fans", libera));
        this->pvBPMFans.push_back(pv);
    }

    foreach(QEpicsPV* pv, pvBPMTemps)
        QObject::connect(pv, SIGNAL(valueChanged(QVariant&)), this, SLOT(onLiberaHealthChanged()));
    foreach(QEpicsPV* pv, pvBPMFans)
        QObject::connect(pv, SIGNAL(valueChanged(QVariant&)), this, SLOT(onLiberaHealthChanged()));
}

void FormSRLiberaMain::ledSyncStatus_Changed()
{
    int sync = 0;
    for(int i=0;i<48;i++)
    {
        if(pvLedSync[i]->get().toInt() == 2)
            sync++;
    }

    ui->ledSync->setValue(0);
    if(sync == 0)
    {
        ui->ledSync->setColour0Property(Qt::red);
    }
    else if(sync > 0 && sync < 48)
    {
        ui->ledSync->setColour0Property(Qt::yellow);
    }
    else if(sync >= 48)
    {
        ui->ledSync->setColour0Property(Qt::green);
    }
}

FormSRLiberaMain::~FormSRLiberaMain()
{
    delete ui;
}

void FormSRLiberaMain::on_btnSync_clicked()
{
    for(int i=1;i<=12;i++)
        Client::writePV("libera"+QString::number(i)+":sync",1);
}


void FormSRLiberaMain::on_btnHealth_clicked()
{
    this->health = new FormBPMHealth;
    showUI(health);
}

void FormSRLiberaMain::on_btnGDX_clicked()
{
    this->gdx = new FormGDX;
    showUI(gdx);
}

void FormSRLiberaMain::onLiberaHealthChanged()
{
    int major = 0;
    int minor = 0;
    int normal = 0;
    foreach(QEpicsPV* pv, this->pvBPMTemps) {
        double value = pv->get().toDouble();
        if(value <= 65)
            normal = 1;
        else if(value > 65 && value <= 75)
            minor = 1;
        else
            major = 1;
    }

    foreach(QEpicsPV* pv, this->pvBPMFans) {
        double value = pv->get().toDouble();
        if(value <= 6300)
            normal = 1;
        else if(value > 6300 && value <= 6450)
            minor = 1;
        else
            major = 1;
    }

    QPalette p = ui->btnHealth->palette();
    if(major)
        p.setColor(QPalette::Button, Qt::red);
    else if(minor)
        p.setColor(QPalette::Button, Qt::yellow);
    else
        p.setColor(QPalette::Button, Qt::green);
    ui->btnHealth->setAutoFillBackground(true);
    ui->btnHealth->setPalette(p);
    ui->btnHealth->update();
}

void FormSRLiberaMain::on_btnEnablePm_clicked()
{
    for(int i=1;i<=12;i++)
    {
        for (int j=1; j<=4; j++)
        {
            Client::writePV("libera"+QString::number(i)+":bpm"+QString::number(j)+":pm:capture_sp",1);
        }
    }

    Client::writePV("GBL-TI-EVR1-P5:enable",0);
    QThread::sleep(3);

    for (int i=1; i<=12; i++)
    {
        Client::writePV("libera"+QString::number(i)+":sync",1);
    }

    Client::writePV("GBL-TI-EVR1-P5:enable",1);

}
