#include "vacuum_cell_widget.h"
#include "ui_vacuum_cell_widget.h"

VacuumCellWidget::VacuumCellWidget(int cell, char section, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VacuumCellWidget)
{
    ui->setupUi(this);

    QString ipPrefix = QString::asprintf("cell=%02d,", cell);
    int img = 1;
    int ip;
    if(section == 'S') {
        ui->lblIP1->setVariableNameSubstitutionsProperty(ipPrefix + ",ip=1");
        ui->lblIP2->setVariableNameSubstitutionsProperty(ipPrefix + ",ip=2");
        ui->lblIP3->setVariableNameProperty(""); ui->lblIP3->setText(""); ui->lblIP3->setFrameShape(QLabel::NoFrame);
        ui->lblIP4->setVariableNameProperty(""); ui->lblIP4->setText(""); ui->lblIP4->setFrameShape(QLabel::NoFrame);
    }
    else if(section == 'L') {
        ui->lblIP1->setVariableNameSubstitutionsProperty(ipPrefix + ",ip=1");
        ui->lblIP2->setVariableNameSubstitutionsProperty(ipPrefix + ",ip=2");
        ui->lblIP3->setVariableNameSubstitutionsProperty(ipPrefix + ",ip=3");
        ui->lblIP4->setVariableNameProperty(""); ui->lblIP4->setText(""); ui->lblIP4->setFrameShape(QLabel::NoFrame);
    }
    else if(section == 'B') {
        img = 2;
        if(cell % 2 == 0 && cell != 16)
            ip = 3;
        else
            ip = 4;
        ui->lblIP1->setVariableNameSubstitutionsProperty(ipPrefix + ",ip=" + QString::number(ip));
        ui->lblIP2->setVariableNameSubstitutionsProperty(ipPrefix + ",ip=" + QString::number(ip + 1));
        ui->lblIP3->setVariableNameSubstitutionsProperty(ipPrefix + ",ip=" + QString::number(ip + 2));
        ui->lblIP4->setVariableNameSubstitutionsProperty(ipPrefix + ",ip=" + QString::number(ip + 3));
    }
    else if(section == 'T') {
        if(cell == 1)
            ip = 1;
        else
            ip = 5;
        ui->lblIP1->setVariableNameProperty(QString("TL2-VA-IP%1:getPressure").arg(ip));
        ui->lblIP2->setVariableNameProperty(QString("TL2-VA-IP%1:getPressure").arg(ip + 1));
        ui->lblIP3->setVariableNameProperty(QString("TL2-VA-IP%1:getPressure").arg(ip + 2));
        ui->lblIP4->setVariableNameProperty(QString("TL2-VA-IP%1:getPressure").arg(ip + 3));
        ui->lblIMG->setVariableNameProperty(QString("TL2-VA-IMG%1:getPressure").arg(cell));
    }
    else if(section == 'I') {
        if(cell == 1) {
            ui->lblIP1->setVariableNameProperty(QString("BOC01-VA-IP1:getPressure"));
            ui->lblIP2->setVariableNameProperty(QString("BOC02-VA-IP1:getPressure"));
            ui->lblIP3->setVariableNameProperty(QString("BOC03-VA-IP1:getPressure"));
            ui->lblIP4->setVariableNameProperty(QString("BOC04-VA-IP1:getPressure"));
        }
        else {
            ui->lblIP1->setVariableNameProperty(QString("BOC05-VA-IP1:getPressure"));
            ui->lblIP2->setVariableNameProperty(QString("BOC06-VA-IP1:getPressure"));
            ui->lblIP3->setVariableNameProperty(QString("BOC06-VA-IP2:getPressure"));
            ui->lblIP4->setVariableNameProperty(""); ui->lblIP4->setText(""); ui->lblIP4->setFrameShape(QLabel::NoFrame);
        }

        ui->lblIMG->setVariableNameProperty(QString("BOC0%1-VA-IMG1:getPressure").arg(cell));
    }
    else if(section == 'M') {
        ui->lblIMG->setVariableNameProperty("MI-VA-IMG:getPressure");
        ui->lblIP1->setVariableNameProperty(""); ui->lblIP1->setText(""); ui->lblIP1->setFrameShape(QLabel::NoFrame);
        ui->lblIP2->setVariableNameProperty(""); ui->lblIP2->setText(""); ui->lblIP2->setFrameShape(QLabel::NoFrame);
        ui->lblIP3->setVariableNameProperty(""); ui->lblIP3->setText(""); ui->lblIP3->setFrameShape(QLabel::NoFrame);
        ui->lblIP4->setVariableNameProperty(""); ui->lblIP4->setText(""); ui->lblIP4->setFrameShape(QLabel::NoFrame);
    }

    // Exceptions ...
    if(cell == 3 && section == 'L') {
        ui->lblIP4->setVariableNameProperty(QString::asprintf("SRC03-VA-IP4:getPressure"));
        ui->lblIP4->setFrameShape(QLabel::StyledPanel);
    }
    if(cell == 9 && section == 'L') {
        ui->lblIP3->setVariableNameProperty("");
        ui->lblIP3->setText("");
        ui->lblIP3->setFrameShape(QLabel::NoFrame);
    }
    if(cell == 11 && section == 'L') {
        ui->lblIP1->setVariableNameProperty("");
        ui->lblIP1->setText("");
        ui->lblIP1->setFrameShape(QLabel::NoFrame);
    }

    if(section == 'B' && cell == 16)
        ui->lblIMG->setVariableNameProperty("SRC16-VA-IMG-PNHL:getPressure");
    else if(section == 'B' && cell % 2 == 0 && cell != 10) {
        ui->lblIMG->setVariableNameProperty("");
        ui->lblIMG->setText("");
        ui->lblIMG->setFrameShape(QLabel::NoFrame);
    }

    QString imgPrefix = QString::asprintf("group=SRC%02d-VA-IMG%d", cell, img);
    ui->lblIMG->setVariableNameSubstitutionsProperty(imgPrefix);
    // ui->lblTitle->setText(QString::asprintf("C%02d%c", cell, section));
    switch(section) {
    case 'S':
        ui->lblTitle->setText("Short");
        break;
    case 'B':
        ui->lblTitle->setText("Bending");
        break;
    case 'L':
        ui->lblTitle->setText("Long");
        break;
    case 'T':
        ui->lblTitle->setText("TL2-" + QString::number(cell));
        break;
    case 'I':
        ui->lblTitle->setText("Booster-" + QString::number(cell));
        break;
    case 'M':
        ui->lblTitle->setText("Microtron");
        break;
    default:
        ui->lblTitle->setText("");
    }

    if(cell == 16 && section == 'L') {
        ui->lblTitle->setText("Short");
    }
}

VacuumCellWidget::~VacuumCellWidget()
{
    delete ui;
}
