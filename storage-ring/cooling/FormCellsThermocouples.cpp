#include "FormCellsThermocouples.h"
#include "ui_FormCellsThermocouples.h"

FormCellsThermocouples::FormCellsThermocouples(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormCellsThermocouples)
{
    ui->setupUi(this);
    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));

    for (int index = 3; index <= 11; ++index)
        this->ui->ltThermocouplesCol1->addWidget(new sr_cooling_thermocouple_widget(index));

    for (int index = 1; index <= 3; ++index)
        this->ui->ltThermocouplesCol2->addWidget(new sr_cooling_thermocouple_widget(index));
    for (int index = 11; index <= 16; ++index)
        this->ui->ltThermocouplesCol2->addWidget(new sr_cooling_thermocouple_widget(index));
}

FormCellsThermocouples::~FormCellsThermocouples()
{
    delete ui;
}
