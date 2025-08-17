#include "FormCorrectorDetails.h"
#include "ui_FormCorrectorDetails.h"

#include <QStyle>

FormCorrectorDetails::FormCorrectorDetails(QString group, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormCorrectorDetails)
{
    ui->setupUi(this);
    this->group = group;

    CONNECT_CLOSE_BUTTON;
    SET_GROUP(QESimpleShape);
    SET_GROUP(QELabel);
    SET_GROUP(QEPushButton);
    SET_GROUP(QENumericEdit);

    this->setWindowTitle(this->group + " Details");

    QFile file(":/configurations/sr-correctors-faults.txt", this);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Warning", "Could not open messages file.", QMessageBox::Ok);
        return;
    }

    QTextStream faults(&file);
    QString line;
    QStringList items;
    int code;
    QString message;
    while(!faults.atEnd()) {
        line = faults.readLine();
        items = line.split(',');
        code = items[0].toUInt(Q_NULLPTR, 16);
        message = items[1];

        this->messages[code] = message;
    }

    this->faults = new QEpicsPV(this->group + ":getFaults");
    this->state  = new QEpicsPV(this->group + ":getStateHandler");
    QObject::connect(this->faults, SIGNAL(valueChanged(QVariant)), this, SLOT(faultsChanged(QVariant)));
    QObject::connect(this->state,  SIGNAL(valueChanged(QVariant)), this, SLOT(stateHandlerChanged()));

    this->readings = NULL;
    this->tuning = NULL;
    this->plotter = NULL;
}

FormCorrectorDetails::~FormCorrectorDetails()
{
    this->messages.clear();
    delete ui;
}

void FormCorrectorDetails::faultsChanged(QVariant value)
{
    int error = value.toInt();
    for(int i = 0; i <= 3; i++) {
        QLabel* label = this->findChild<QLabel*>("lblFaults_" + QString::number(i));
        error = (error >> (i * 8)) & 0xFF;
        if(error >= 0 && error <= 0xE1) {
            label->setText( this->messages[ error ] );
            if(i == 0) {
                if(error == 0) {
                    ui->ledFault->setLedType(QSimpleShape::Error);
                    ui->ledFault->setValue(0);
                }
                else if(error == 0x32 || error == 0x37 || error == 0x38 || error == 0x46 || error == 0x47 || error == 0x4A) {
                    ui->ledFault->setLedType(QSimpleShape::Warning);
                    ui->ledFault->setValue(1);
                }
                else {
                    ui->ledFault->setLedType(QSimpleShape::Error);
                    ui->ledFault->setValue(1);
                }
            }
        }
        else {
            ui->ledFault->setValue(0);
            label->setText( "N/A" );
        }
    }
}

void FormCorrectorDetails::stateHandlerChanged()
{
    int value = this->state->get().toInt();
    if(value == 2) {
        this->ui->btnOFF->setEnabled(true);
        this->ui->btnON->setEnabled(false);
        this->ui->ledOFF->setValue(0);
        this->ui->ledON->setValue(1);
    }
    else if(value == 1) {
        this->ui->btnOFF->setEnabled(false);
        this->ui->btnON->setEnabled(true);
        this->ui->ledOFF->setValue(1);
        this->ui->ledON->setValue(0);
    }
}

void FormCorrectorDetails::on_btnPlotter_clicked()
{
    OPEN_UI(this->plotter, FormCorrectorPlotter, this->group);
}

void FormCorrectorDetails::on_btnTuning_clicked()
{
    OPEN_UI(this->tuning, FormCorrectorTuning, this->group);
}

void FormCorrectorDetails::on_btnReadings_clicked()
{
    OPEN_UI(this->readings, FormCorrectorsReadings, this->group, this);
}
