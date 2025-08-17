#include "uiSR_RFTempratures.h"
#include "ui_uiSR_RFTempratures.h"

uiSR_RFTempratures::uiSR_RFTempratures(int ssa, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::uiSR_RFTempratures)
{
    ui->setupUi(this);
    QString title=ui->title_label->text();
    ui->title_label->setText(title.replace("$(ssa)", QString::number(ssa)));
    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));

    //set $(ssa) for labels
    for(int i = 0; i < 11; i++)
    {
        // pvTempAvg[i] = new QEpicsPV(QString("").sprintf("SRC03-RF-SSA%d-DIS%02d:getTemperatures", ssa, i));
        pvTempAvg.push_back(new QEpicsPV(QString::asprintf("SRC03-RF-SSA%d-DIS%02d:getTemperatures", ssa, i)));
    }

    for(int i = 0; i <= 10; i++)
        QObject::connect(pvTempAvg[i], SIGNAL(valueChanged(QVariant)), this, SLOT(onTemperaturesChanged()));

    QString substitutions;
    foreach (QELabel* w, this->findChildren<QELabel*>()) {
        substitutions = w->getVariableNameSubstitutionsProperty();
        substitutions += ",ssa=" + QString::number(ssa);
        w->setVariableNameSubstitutionsProperty(substitutions);
    }
}

uiSR_RFTempratures::~uiSR_RFTempratures()
{
    delete ui;
}

void uiSR_RFTempratures::onDissipatorsTemperaturesChanged()
{
//    QEpicsPV* pv = (QEpicsPV*) sender();
//    int id = pv->pv().split(":")[0].split("-")[3].mid(3, 2).toInt();
//    QList<QVariant> disList = pvDisTemp[id]->get().toList();
//    if(disList.size() < 64)
//        return;

//    QString value;
//    bool status = false;
//    for(int i = 0; i < (id == 0 ? 20 : 64); i++)
//    {
//        // value += getChar(disList[i].toInt());
//        value += disList[i].toChar();
//        if((i + 1) % 4 == 0)
//        {
//            this->findChild<QLabel*>(QString().sprintf(id == 0 ? "lblDIS%02dM%d" : "lblTmepDIS%02dM%d", id, (i / 4) + 1))
//                ->setText(QString::number(value.toInt(&status, 16) / 100.0) + " C");
//            value = "";
//        }
//    }
}

//get Average Temprature
void uiSR_RFTempratures::onTemperaturesChanged()
{
//    int count = 0;
//    double sum = 0.0;
//    QList<QVariant> data;
//    for(int i = 1; i <= 10; i++)
//    {
//        data = pvTempAvg[i]->get().toList();
//        if(data.size() < 16)
//            continue;

//        count++;
//        for(int j = 0; j < 16; j++)
//        {
//            sum += data[j].toDouble();
//        }
//    }
//    if(count == 0)
//        return;
//    ui->lblAvgTemp->setText(QString::number(sum/(count * 16.0)) + " C");

//    data = pvTempAvg[0]->get().toList();
//    if(data.size() < 5)
//        return;

//    sum = 0.0;
//    for(int j = 0; j < 5; j++)
//    {
//        sum += data[j].toDouble();
//    }

//    ui->lblAvgDriverTemp->setText(QString::number(sum / 5) + " C");
}
