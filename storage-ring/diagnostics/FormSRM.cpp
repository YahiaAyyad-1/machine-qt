#include "FormSRM.h"
#include "ui_FormSRM.h"

FormSRM::FormSRM(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::FormSRM)
{
    ui->setupUi(this);
    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));

    this->pvShutterFault  = new QEpicsPV("SRC14-VA-SHUTTER:isFault");
    this->pvShutterClosed = new QEpicsPV("SRC14-VA-SHUTTER:isClosed");
    this->pvShutterOpened = new QEpicsPV("SRC14-VA-SHUTTER:isOpen");
    QObject::connect(pvShutterFault,  SIGNAL(valueChanged(QVariant)), this, SLOT(onShutterStateChanged()));
    QObject::connect(pvShutterClosed, SIGNAL(valueChanged(QVariant)), this, SLOT(onShutterStateChanged()));
    QObject::connect(pvShutterOpened, SIGNAL(valueChanged(QVariant)), this, SLOT(onShutterStateChanged()));
}

FormSRM::~FormSRM()
{
    delete ui;
}

void FormSRM::onShutterStateChanged()
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
