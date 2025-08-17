#include "camera_widget.h"
#include "ui_camera_widget.h"

CameraWidget::CameraWidget(QString prefix, QString cam, QString model, QString profile, QString docker, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraWidget)
{
    ui->setupUi(this);

    ui->label->setText(prefix);

    QString pvPrefix = prefix + ":" + cam;
    ui->ledConnected->setVariableNameSubstitutionsProperty("prefix=" + pvPrefix);
    ui->ledHearbeat->setVariableNameSubstitutionsProperty("prefix=" + pvPrefix);
    ui->lblBusy->setVariableNameSubstitutionsProperty("prefix=" + pvPrefix);
    ui->lblImages->setVariableNameSubstitutionsProperty("prefix=" + pvPrefix);
    ui->lblAcquire->setVariableNameSubstitutionsProperty("prefix=" + pvPrefix);
    ui->btnStop->setVariableNameSubstitutionsProperty("prefix=" + pvPrefix);
    ui->btnStart->setVariableNameSubstitutionsProperty("prefix=" + pvPrefix);

    ui->btnGUI->setProgram(QString("run-basler-cam %1 %2 %3 %4").arg(prefix).arg(cam).arg(model).arg(profile));

    this->dockerImage = docker;
}

CameraWidget::~CameraWidget()
{
    delete ui;
}

void CameraWidget::on_btnRestart_clicked()
{
    QProcess* p = new QProcess;
    p->start("ssh", {"dev.control@10.2.0.28", QString("docker restart %1").arg(dockerImage)});
}

void CameraWidget::on_btnStopIOC_clicked()
{
    QProcess* p = new QProcess;
    p->start("ssh", {"dev.control@10.2.0.28", QString("docker stop %1").arg(dockerImage)});
}
