#include "FormMPS.h"
#include "ui_FormMPS.h"

FormMPS::FormMPS(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormMPS),
    greenColor("#e0eee0"),
    yellowColor("#fce94f"),
    redColor("#f00505")
{
    ui->setupUi(this);
    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
    this->pvShutterFault  = new QEpicsPV("SRC14-VA-SHUTTER:isFault");
    this->pvShutterClosed = new QEpicsPV("SRC14-VA-SHUTTER:isClosed");
    this->pvShutterOpened = new QEpicsPV("SRC14-VA-SHUTTER:isOpen");
    this->pvSextupolesMontitor = new QEpicsPV("SextupolesMontitor:PV");
    this->pvSextupolesIsLatchedInterlock = new QEpicsPV("SRC03-PS-SX:isLatchedInterlock");
    this->pvQuadrupolesMontitor = new QEpicsPV("QuadrupolesMontitor:PV");
    this->pvQuadrupolesIsLatchedInterlock = new QEpicsPV("SRC03-PS-QD:isLatchedInterlock");
    QObject::connect(pvShutterFault,  SIGNAL(valueChanged(QVariant)), this, SLOT(onShutterStateChanged()));
    QObject::connect(pvShutterClosed, SIGNAL(valueChanged(QVariant)), this, SLOT(onShutterStateChanged()));
    QObject::connect(pvShutterOpened, SIGNAL(valueChanged(QVariant)), this, SLOT(onShutterStateChanged()));
    QObject::connect(pvSextupolesMontitor, SIGNAL(valueChanged(QVariant)), this, SLOT(onSextupolesMontitorPVChanged(QVariant)));
    QObject::connect(pvSextupolesIsLatchedInterlock, SIGNAL(valueChanged(QVariant)), this, SLOT(onSextupolesIsLatchedInterlockChanged(QVariant)));
    QObject::connect(pvQuadrupolesMontitor, SIGNAL(valueChanged(QVariant)), this, SLOT(onQuadrupolesMontitorPVChanged(QVariant)));
    QObject::connect(pvQuadrupolesIsLatchedInterlock, SIGNAL(valueChanged(QVariant)), this, SLOT(onQuadrupolesIsLatchedInterlockChanged(QVariant)));
}

FormMPS::~FormMPS()
{
    delete ui;
}

void FormMPS::on_btnIRreset_clicked()
{
    Client::writePV("D02C01-CO-FLS1:reset", 1);
    Client::writePV("D02C01-VA-ABS:reset", 1);
    Client::writePV("D02-CO-THC:reset", 1);
}

void FormMPS::on_btnReset_clicked()
{
    Client::writePV("SR-VA-IMG:reset", 1);
    Client::writePV("SR-VA-IP:resetInterlocks", 1);
}

void FormMPS::on_btnXAFSreset_clicked()
{
    Client::writePV("FE08-VA-GC1:reset",1);
    Client::writePV("FE08-VA-GV1:reset",1);
    Client::writePV("FE08-VA-PHSH:reset",1);
    Client::writePV("FE08-CO-FLS:reset",1);
}

void FormMPS::on_btnMSreset_clicked()
{
    Client::writePV("I09FE-CO-FLS:resetInterlock",1);
    Client::writePV("I09FE-CO-THC:resetInterlock",1);
    Client::writePV("I09FE-VA:resetInterlock",1);
    Client::writePV("I09FE-VA-GV:resetInterlock",1);
}

void FormMPS::on_btnBEATSreset_clicked()
{
    Client::writePV("I10-VA:resetInterlock",1);
    Client::writePV("I10-CO:resetInterlock",1);
}

void FormMPS::on_btnHESEBreset_clicked()
{
    Client::writePV("I11FE-CO-THC:resetInterlock",1);
    Client::writePV("I11FE-CO-FLS:resetInterlock",1);
    Client::writePV("I11FE-VA-GC1:resetInterlock",1);
    Client::writePV("I11FE-VA-GV:resetInterlock",1);
}

void FormMPS::on_btnOpenXAFS_clicked()
{
    Client::writePV("FE08-VA-GV1:setOpen", 1);
    Client::writePV("FE08-VA-GV1:reset", 1);
}

void FormMPS::on_btnResetSRM_clicked()
{
    for(int cell = 1; cell <= 15; cell += 2) {
        Client::writePV(QString::asprintf("SRC%02d-VA-GV1:reset", cell), 1);
        Client::writePV(QString::asprintf("SRC%02d-VA-GV2:reset", cell), 1);
    }

    Client::writePV("SRC14-VA-GV:reset", 1);
    Client::writePV("SRC16-VA-PHC-GV:reset", 1);
}

void FormMPS::onShutterStateChanged()
{
    int get_shutter_is_closed = pvShutterClosed->get().toInt();
    int get_shutter_is_open = pvShutterOpened->get().toInt();
    int get_shutter_is_fault = pvShutterFault->get().toInt();

    if (get_shutter_is_fault == 1) {
        ui->shutter_state->setValue(0);
    }
    else if (get_shutter_is_closed == 1) {
        ui->shutter_state->setValue(1);
    }
    else if (get_shutter_is_open == 1) {
        ui->shutter_state->setValue(2);
    }
    else
        ui->shutter_state->setValue(3);
}

void FormMPS::on_btnBeamlinesInterlocks_clicked()
{
    FormBeamlinesInterlocks* beamlines_interlocks = new FormBeamlinesInterlocks(this);
    beamlines_interlocks->show();
}

void FormMPS::on_btnResetSXT_clicked()
{
    Client::writePV("SRC03-PS-SX:resetInterlock", 1);
    Client::writePV("SextupolesMontitor:PV", "");
    Client::writePV("SextupolesMontitor:Time", "");
}

void FormMPS::on_btnResetQD_clicked()
{
    Client::writePV("SRC03-PS-QD:resetInterlock", 1);
    Client::writePV("QuadrupolesMontitor:PV", "");
    Client::writePV("QuadrupolesMontitor:Time", "");
}

void FormMPS::onSextupolesMontitorPVChanged(const QVariant &pvVal)
{
    if (pvVal.toBool())
    {
        if (this->pvSextupolesIsLatchedInterlock->getUpdated().toBool())
        {
            this->ui->sextupolesViolationPv->setStyleSheet({ "background-color: " + yellowColor });
            this->ui->sextupolesViolationTime->setStyleSheet({ "background-color: " + yellowColor });
        } else
        {
            this->ui->sextupolesViolationPv->setStyleSheet({ "background-color: " + redColor });
            this->ui->sextupolesViolationTime->setStyleSheet({ "background-color: " + redColor });
        }
    } else
    {
        this->ui->sextupolesViolationPv->setStyleSheet({ "background-color: " + greenColor });
        this->ui->sextupolesViolationTime->setStyleSheet({ "background-color: " + greenColor });
    }
}

void FormMPS::onSextupolesIsLatchedInterlockChanged(const QVariant &val)
{
    if (!val.toBool())
    {
        this->ui->sextupolesViolationPv->setStyleSheet({ "background-color: " + redColor });
        this->ui->sextupolesViolationTime->setStyleSheet({ "background-color: " + redColor });
    }
}

void FormMPS::onQuadrupolesMontitorPVChanged(const QVariant &pvVal)
{
    if (pvVal.toBool())
    {
        if (this->pvQuadrupolesIsLatchedInterlock->getUpdated().toBool())
        {
            this->ui->quadrupolesViolationPv->setStyleSheet({ "background-color: " + yellowColor });
            this->ui->quadrupolesViolationTime->setStyleSheet({ "background-color: " + yellowColor });
        } else
        {
            this->ui->quadrupolesViolationPv->setStyleSheet({ "background-color: " + redColor });
            this->ui->quadrupolesViolationTime->setStyleSheet({ "background-color: " + redColor });
        }
    } else
    {
        this->ui->quadrupolesViolationPv->setStyleSheet({ "background-color: " + greenColor });
        this->ui->quadrupolesViolationTime->setStyleSheet({ "background-color: " + greenColor });
    }
}

void FormMPS::onQuadrupolesIsLatchedInterlockChanged(const QVariant &val)
{
    if (!val.toBool())
    {
        this->ui->quadrupolesViolationPv->setStyleSheet({ "background-color: " + redColor });
        this->ui->quadrupolesViolationTime->setStyleSheet({ "background-color: " + redColor });
    }
}
