#include "sr_cooling_thermocouple_widget.h"
#include "ui_sr_cooling_thermocouple_widget.h"

sr_cooling_thermocouple_widget::sr_cooling_thermocouple_widget(int cellNumber, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sr_cooling_thermocouple_widget)
{
    ui->setupUi(this);

    QString enablePvName = QString::asprintf("SRC%02d-THC:enable", cellNumber);

    this->ui->lblCellName->setText(QString::asprintf("Cell %02d", cellNumber));
    this->ui->chkBoxEnable->setVariableNameProperty(enablePvName);
    this->ui->temperature->setVariableNameProperty(QString::asprintf("SRC%02d-CO-THC1:getTemperature", cellNumber));
    this->ui->ledEnable->setVariableNameProperty(QString::asprintf("SRC%02d-THC:isEnabled", cellNumber));

    this->enablePv = new QEpicsPV(enablePvName);

    QObject::connect(enablePv, SIGNAL(valueInited(const QVariant &)), this, SLOT(onEnablePvchange(const QVariant &)));
    QObject::connect(enablePv, SIGNAL(valueChanged(const QVariant &)), this, SLOT(onEnablePvchange(const QVariant &)));
}

sr_cooling_thermocouple_widget::~sr_cooling_thermocouple_widget()
{
    delete ui;
}

void sr_cooling_thermocouple_widget::onEnablePvchange(const QVariant &val)
{
    this->ui->chkBoxEnable->setChecked(val.toBool());
}
