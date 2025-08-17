#include "uiTL2PowerSupply.h"
#include "ui_uiTL2PowerSupply.h"

#include "client.h"

uiTL2PowerSupply::uiTL2PowerSupply(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::uiTL2PowerSupply)
{
    ui->setupUi(this);
    QObject::connect(ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));

    ui->layoutBM->addWidget(new TL2PowerSupplyWidget("TL2-PS-BM1-X", "getShutdownCondition.B3", "isRemoteShutdown.B2",
                                                    {"TL2-CO-SB1-HBM1:isTemperatureInterlock", "TL2-CO-SB1-HBM1:isFlowInterlock"}, this));
    ui->layoutBM->addWidget(new TL2PowerSupplyWidget("TL2-PS-BM1-Y", "getShutdownCondition.BD", "isRemoteShutdown.BC",
                                                    {"TL2-CO-SB1-VBM1:isTemperatureInterlock", "TL2-CO-SB1-VBM1:isFlowInterlock"}, this));
    ui->layoutBM->addWidget(new TL2PowerSupplyWidget("TL2-PS-BM2-X", "getShutdownCondition.B3", "isRemoteShutdown.B2",
                                                    {"TL2-CO-SB2-HBM2:isTemperatureInterlock", "TL2-CO-SB2-HBM2:isFlowInterlock"}, this));
    ui->layoutBM->addWidget(new TL2PowerSupplyWidget("TL2-PS-BM2-Y", "getShutdownCondition.BD", "isRemoteShutdown.BC",
                                                    {"TL2-CO-SB1-VBM2:isTemperatureInterlock", "TL2-CO-SB1-VBM2:isFlowInterlock"}, this));

    QStringList pvList;
    for (int i = 1; i <= 7; i++) {
        if (i == 3)
            pvList = QStringList({"TL2-CO-SB1-Q3:isTemperatureInterlock", "TL2-CO-SB1-Q3:isFlowInterlock"});
        else if (i == 5)
            pvList = QStringList({"TL2-CO-SB2-Q5:isTemperatureInterlock", "TL2-CO-SB2-Q5:isFlowInterlock"});
        else if (i == 7)
            pvList = QStringList({"TL2-CO-SB2-Q7:isTemperatureInterlock", "TL2-CO-SB2-Q7:isFlowInterlock"});
        else
            pvList = QStringList({});

        ui->layoutQuads->addWidget(new TL2PowerSupplyWidget("TL2-PS-Q" + QString::number(i), "getShutdownCondition.B3", "isRemoteShutdown.B2", pvList, this));
    }

    ui->layoutTHS->addWidget(new TL2PowerSupplyWidget("TL2-PS-THS", "getShutdownCondition.B3", "isRemoteShutdown.B2",
                                                     {"TL2-CO-SB2-THS:isTemperatureInterlock", "TL2-CO-SB2-THS:isFlowInterlock"}, this));

    int i = 1;
    for (QString name : {"STY1", "STY2", "STX2", "STY3", "STX3"}) {
        ui->layoutCR->addWidget(new TL2CorrectorWidget("TL2-PS-" + name, "TL2-PS-CR" + QString::number(i++), this));
    }
}

uiTL2PowerSupply::~uiTL2PowerSupply()
{
    delete ui;
}
