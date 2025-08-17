#include "FormInjection.h"
#include "ui_FormInjection.h"

FormInjection::FormInjection(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormInjection)
{
    ui->setupUi(this);
    CONNECT_CLOSE_BUTTON;

    QString jsonText;
    QString listName;
    QJsonParseError error;
    QJsonDocument document;
    QJsonValue top;
    QJsonArray pvLists;
    QJsonArray pvNames;
    QFile config(":/configurations/re-injection-pv-lists.json");
    config.open(QIODevice::ReadOnly | QIODevice::Text);
    jsonText = config.readAll();
    config.close();

    document = QJsonDocument::fromJson(jsonText.toUtf8(), &error);
    top = document.object().value("pv_lists");
    pvLists = top.toArray();
    for(auto object : pvLists) {
        listName = object.toObject().value("name").toString();
        pvNames = object.toObject().value("pvs").toArray();

        QList<QEpicsPV*> list;
        for(auto pv : pvNames) {
            list.push_back(new QEpicsPV(pv.toString()));
        }
        this->pvListsMap[listName] = list;
    }

    this->rfRampTimer = new QTimer;
    QObject::connect(this, SIGNAL(destroyed(QObject*)), this->rfRampTimer, SLOT(stop()));

    do
    {
        int i = 0;
        this->pvBM = new QEpicsPV("SR-PS-BM:getStateHandler");

        // pvListSX moved to DB.
        this->pvListSX.push_back(new QEpicsPV("SR-PS-SF1:getStateHandler"));
        this->pvListSX.push_back(new QEpicsPV("SR-PS-SF2:getStateHandler"));
        this->pvListSX.push_back(new QEpicsPV("SR-PS-SD1:getStateHandler"));
        this->pvListSX.push_back(new QEpicsPV("SR-PS-SD2:getStateHandler"));

        // pvListMDB moved to DB.
        this->pvListMDB.push_back(new QEpicsPV("SR-MDB:isPowerON"));
        this->pvListMDB.push_back(new QEpicsPV("SR-SMDB-Q1:isPowerON"));
        this->pvListMDB.push_back(new QEpicsPV("SR-SMDB-Q2:isPowerON"));
        this->pvListMDB.push_back(new QEpicsPV("SR-SMDB-Q3:isPowerON"));
        this->pvListMDB.push_back(new QEpicsPV("SR-SMDB-Q4:isPowerON"));
        this->pvListMDB.push_back(new QEpicsPV("SR-RF-MDB:isPowerON"));
        this->pvListMDB.push_back(new QEpicsPV("SR-RF-SMDB:isPowerON"));
        this->pvListMDB.push_back(new QEpicsPV("SR-MDB:isEmergency"));
        this->pvListMDB.push_back(new QEpicsPV("SR-SMDB-Q1:isEmergency"));
        this->pvListMDB.push_back(new QEpicsPV("SR-SMDB-Q2:isEmergency"));
        this->pvListMDB.push_back(new QEpicsPV("SR-SMDB-Q3:isEmergency"));
        this->pvListMDB.push_back(new QEpicsPV("SR-SMDB-Q4:isEmergency"));
        this->pvListMDB.push_back(new QEpicsPV("SR-RF-MDB:isEmergency"));
        this->pvListMDB.push_back(new QEpicsPV("SR-RF-SMDB:isEmergency"));

        // pvListBoosterVA moved to DB.
        this->pvListBoosterVA.push_back(new QEpicsPV("BOC01-VA-IMG1:getPressure.SEVR"));
        this->pvListBoosterVA.push_back(new QEpicsPV("BOC02-VA-IMG1:getPressure.SEVR"));
        this->pvListBoosterVA.push_back(new QEpicsPV("BOC03-VA-IMG1:getPressure.SEVR"));
        this->pvListBoosterVA.push_back(new QEpicsPV("BOC05-VA-IMG1:getPressure.SEVR"));

        // pvListBoosterPS moved to DB.
        this->pvListBoosterPS.push_back(new QEpicsPV("BO-PS-BM:getRegulationInterlocks"));
        this->pvListBoosterPS.push_back(new QEpicsPV("BO-PS-BM:getMasterHardwareInterlocks"));
        this->pvListBoosterPS.push_back(new QEpicsPV("BO-PS-BM:getMasterSoftwareInterlocks"));
        this->pvListBoosterPS.push_back(new QEpicsPV("BO-PS-BM:getSlave1SoftwareInterlocks"));
        this->pvListBoosterPS.push_back(new QEpicsPV("BO-PS-BM:getSlave1HardwareInterlocks"));
        this->pvListBoosterPS.push_back(new QEpicsPV("BO-PS-BM:getSlave2SoftwareInterlocks"));
        this->pvListBoosterPS.push_back(new QEpicsPV("BO-PS-BM:getSlave2HardwareInterlocks"));
        this->pvListBoosterPS.push_back(new QEpicsPV("BO-PS-QF:getRegulationInterlocks"));
        this->pvListBoosterPS.push_back(new QEpicsPV("BO-PS-QF:getHardwareInterlocks"));
        this->pvListBoosterPS.push_back(new QEpicsPV("BO-PS-QF:getSoftwareInterlocks"));
        this->pvListBoosterPS.push_back(new QEpicsPV("BO-PS-QD:getRegulationInterlocks"));
        this->pvListBoosterPS.push_back(new QEpicsPV("BO-PS-QD:getHardwareInterlocks"));
        this->pvListBoosterPS.push_back(new QEpicsPV("BO-PS-QD:getSoftwareInterlocks"));

        this->pvListBL = new QEpicsPV("SR-RF-CAV:getCavitiesVoltage");
        QObject::connect(pvListBL, &QEpicsPV::valueChanged, this, [this](){ ui->ledRFVolt->setValue(pvListBL->get().toDouble() > 1200); });

        for(i = 1; i <= 6; i++)
            for(int j = 1; j <= 5; j++)
                this->pvListBoosterCO.push_back(new QEpicsPV(QString::asprintf("BOC%02d-CO-SB%d:isInterlock", i, j)));

        for(i = 1; i <= 16; i++)
        {
            this->pvListQF.push_back(new QEpicsPV(QString::asprintf("SRC%02d-PS-QF1:getStateHandler", i)));
            this->pvListQF.push_back(new QEpicsPV(QString::asprintf("SRC%02d-PS-QF2:getStateHandler", i)));
            this->pvListQD.push_back(new QEpicsPV(QString::asprintf("SRC%02d-PS-QD1:getStateHandler", i)));
            this->pvListQD.push_back(new QEpicsPV(QString::asprintf("SRC%02d-PS-QD2:getStateHandler", i)));
//            this->pvListHC.push_back(new QEpicsPV(QString::asprintf("SRC%02d-PS-HC1:getFaults", i)));
//            this->pvListHC.push_back(new QEpicsPV(QString::asprintf("SRC%02d-PS-HC2:getFaults", i)));
            this->pvListVC.push_back(new QEpicsPV(QString::asprintf("SRC%02d-PS-VC1:getFaults", i)));
            this->pvListVC.push_back(new QEpicsPV(QString::asprintf("SRC%02d-PS-VC2:getFaults", i)));

            if(i % 2 != 0) {
                this->pvListSQ.push_back(new QEpicsPV(QString::asprintf("SRC%02d-PS-SQ1:getFaults", i)));

                this->valve1FaultPVs.push_back(new QEpicsPV(QString::asprintf("SRC%02d-VA-GV1:isFault",  i)));
                this->valve1ClosePVs.push_back(new QEpicsPV(QString::asprintf("SRC%02d-VA-GV1:isClosed", i)));
                this->valve1OpenPVs.push_back(new  QEpicsPV(QString::asprintf("SRC%02d-VA-GV1:isOpen",   i)));

                this->valve2FaultPVs.push_back(new QEpicsPV(QString::asprintf("SRC%02d-VA-GV2:isFault",  i)));
                this->valve2ClosePVs.push_back(new QEpicsPV(QString::asprintf("SRC%02d-VA-GV2:isClosed", i)));
                this->valve2OpenPVs.push_back(new  QEpicsPV(QString::asprintf("SRC%02d-VA-GV2:isOpen",   i)));
            }

            QStringList names = {"SF1", "QF1", "QD1", "SD1", "BM", "SD2", "QD2", "QF2", "SF2"};
            for(QString name : names) {
                this->pvListSRFS.push_back(new QEpicsPV(QString("SRC%1-MA-%2:isFlowInterlock").arg(i, 2).arg(name)));
                this->pvListSRTS.push_back(new QEpicsPV(QString("SRC%1-MA-%2:isTemperatureInterlock").arg(i, 2).arg(name)));
            }

            if(i == 3)
            {
                for(int c = 1; c <= 5; c++)
                {
                    this->pvListIMG.push_back(new QEpicsPV(QString::asprintf("SRC%02d-VA-IMG%d-REL1:isInterlock", i, c)));
                    this->pvListIMG.push_back(new QEpicsPV(QString::asprintf("SRC%02d-VA-IMG%d-REL2:isInterlock", i, c)));
                }
            }
            else if(i % 2 == 0)
            {
                this->pvListIMG.push_back(new QEpicsPV(QString::asprintf("SRC%02d-VA-IMG1-REL1:isInterlock", i)));
                this->pvListIMG.push_back(new QEpicsPV(QString::asprintf("SRC%02d-VA-IMG1-REL2:isInterlock", i)));
            }
            else
            {
                this->pvListIMG.push_back(new QEpicsPV(QString::asprintf("SRC%02d-VA-IMG1-REL1:isInterlock", i)));
                this->pvListIMG.push_back(new QEpicsPV(QString::asprintf("SRC%02d-VA-IMG1-REL2:isInterlock", i)));
                this->pvListIMG.push_back(new QEpicsPV(QString::asprintf("SRC%02d-VA-IMG2-REL1:isInterlock", i)));
                this->pvListIMG.push_back(new QEpicsPV(QString::asprintf("SRC%02d-VA-IMG2-REL2:isInterlock", i)));
            }
        }

        this->valve1FaultPVs.push_back(new QEpicsPV("SRC14-VA-GV:isFault"));
        this->valve1ClosePVs.push_back(new QEpicsPV("SRC14-VA-GV:isClosed"));
        this->valve1OpenPVs.push_back(new QEpicsPV("SRC14-VA-GV:isOpen"));
        this->valve2FaultPVs.push_back(new QEpicsPV("SRC14-VA-GV:isFault"));
        this->valve2ClosePVs.push_back(new QEpicsPV("SRC14-VA-GV:isClosed"));
        this->valve2OpenPVs.push_back(new QEpicsPV("SRC14-VA-GV:isOpen"));

        this->valve1FaultPVs.push_back(new QEpicsPV("SRC16-VA-PHC-GV:isFault"));
        this->valve1ClosePVs.push_back(new QEpicsPV("SRC16-VA-PHC-GV:isClosed"));
        this->valve1OpenPVs.push_back(new QEpicsPV("SRC16-VA-PHC-GV:isOpen"));
        this->valve2FaultPVs.push_back(new QEpicsPV("SRC16-VA-PHC-GV:isFault"));
        this->valve2ClosePVs.push_back(new QEpicsPV("SRC16-VA-PHC-GV:isClosed"));
        this->valve2OpenPVs.push_back(new QEpicsPV("SRC16-VA-PHC-GV:isOpen"));

        for(i = 1; i <= 12; i++)
        {
            for(int j = 1; j <= 4; j++)
            {
                this->pvListBPM.push_back(new QEpicsPV(QString::asprintf("libera%d:bpm%d:ilk:enabled_mon", i, j)));
                this->pvListBPMILK.push_back(new QEpicsPV(QString("SR-DI-LBR%1-BPM%2:getInterlocks").arg(i).arg(j)));
            }
        }

        for(i = 1; i <= 7; i++)
        {
            this->pvTL2Quads.push_back(new QEpicsPV(QString::asprintf("TL2-PS-Q%d:getShutdownCondition.B3", i)));
            this->pvTL2Quads.push_back(new QEpicsPV(QString::asprintf("TL2-PS-Q%d:getShutdownCondition.SEVR", i)));
            if(i <= 5) {
                this->pvTL2Corr.push_back(new QEpicsPV(QString::asprintf("TL2-PS-CR%d:getStatus", i)));
                this->pvTL2Corr.push_back(new QEpicsPV(QString::asprintf("TL2-PS-CR%d:getStatus.SEVR", i)));
            }
        }
        this->pvTL2THS.push_back(new QEpicsPV(QString("TL2-PS-THS:getShutdownCondition.B3")));
        this->pvTL2THS.push_back(new QEpicsPV(QString("TL2-PS-THS:getShutdownCondition.SEVR")));

        this->pvTL2BMX.push_back(new QEpicsPV(QString("TL2-PS-BM1-X:getShutdownCondition.B3")));
        this->pvTL2BMX.push_back(new QEpicsPV(QString("TL2-PS-BM1-X:getShutdownCondition.SEVR")));
        this->pvTL2BMX.push_back(new QEpicsPV(QString("TL2-PS-BM2-X:getShutdownCondition.B3")));
        this->pvTL2BMX.push_back(new QEpicsPV(QString("TL2-PS-BM2-X:getShutdownCondition.SEVR")));

        QObject::connect(pvBM, &QEpicsPV::valueChanged, this, [this]() { ui->ledFaultBM->setValue(pvBM->get().toInt() != 3 && pvBM->get().toInt() != 5); });
        for(i = 1; i <= 4; i++)
            this->pvListRFCO.push_back(new QEpicsPV(QString::asprintf("SR-RF-CR%d:isFlowInterlock", i)));

        this->pvTL2Vacuum.push_back(new QEpicsPV("TL2-VA-IMG1-REL1:isInterlock"));
        this->pvTL2Vacuum.push_back(new QEpicsPV("TL2-VA-IMG1-REL2:isInterlock"));
        this->pvTL2Vacuum.push_back(new QEpicsPV("TL2-VA-IMG2-REL1:isInterlock"));
        this->pvTL2Vacuum.push_back(new QEpicsPV("TL2-VA-IMG2-REL2:isInterlock"));

        for(QEpicsPV* pv : pvListQF)
            QObject::connect(pv, &QEpicsPV::valueChanged, this, [this](){ ui->ledQF->setValue(std::any_of(pvListQF.begin(), pvListQF.end(), [](QEpicsPV* pv) { return pv->get() != 2; })); });
        for(QEpicsPV* pv : pvListQD)
            QObject::connect(pv, &QEpicsPV::valueChanged, this, [this](){ ui->ledQD->setValue(std::any_of(pvListQD.begin(), pvListQD.end(), [](QEpicsPV* pv) { return pv->get() != 2; })); });
        for(QEpicsPV* pv : pvListSX)
            QObject::connect(pv, &QEpicsPV::valueChanged, this, [this](){
                ui->ledSF->setValue(pvListSX[0]->get().toInt() == 2 && pvListSX[1]->get().toInt() == 2);
                ui->ledSD->setValue(pvListSX[2]->get().toInt() == 2 && pvListSX[3]->get().toInt() == 2);
            });
        // for(QEpicsPV* pv : pvListHC)
        for(QEpicsPV* pv : pvListsMap["pvListHC"])
            QObject::connect(pv, SIGNAL(valueChanged(QVariant)), this, SLOT(allPVsChanged()));
        for(QEpicsPV* pv : pvListVC)
            QObject::connect(pv, SIGNAL(valueChanged(QVariant)), this, SLOT(allPVsChanged()));
        for(QEpicsPV* pv : pvListSQ)
            QObject::connect(pv, SIGNAL(valueChanged(QVariant)), this, SLOT(allPVsChanged()));
        for(QEpicsPV* pv : pvListMDB)
            QObject::connect(pv, &QEpicsPV::valueChanged, this, [this](){
                ui->ledMDB->setValue(list_iterator_sum(pvListMDB.begin(), pvListMDB.begin() + 7) == 7 && list_iterator_sum(pvListMDB.begin() + 7, pvListMDB.end()) == 0 );
            });
        for(QEpicsPV* pv : pvListRFCO)
            QObject::connect(pv, &QEpicsPV::valueChanged, this, [this](){ ui->ledRFCO->setValue(list_sum(pvListRFCO) == 0); });
        for(QEpicsPV* pv : pvListBPM)
            QObject::connect(pv, SIGNAL(valueChanged(QVariant)), this, SLOT(allPVsChanged()));
        for(QEpicsPV* pv : pvListBoosterCO)
            QObject::connect(pv, &QEpicsPV::valueChanged, this, [this]() { ui->ledBoosterCO->setValue(list_sum(pvListBoosterCO) == 0); });
        for(QEpicsPV* pv : pvListBoosterPS)
            QObject::connect(pv, &QEpicsPV::valueChanged, this, [this]() {
                this->ui->ledBoosterBM->setValue( std::all_of(pvListBoosterPS.begin(), pvListBoosterPS.begin() + 6, [](QEpicsPV* pv) { return pv->get().toInt() == 0; }) );
                this->ui->ledBoosterQF->setValue(list_iterator_sum(pvListBoosterPS.begin() + 7, pvListBoosterPS.begin() + 9) == 0);
                this->ui->ledBoosterQD->setValue(list_iterator_sum(pvListBoosterPS.begin() + 10, pvListBoosterPS.begin() + 12) == 0);
            });
        for(QEpicsPV* pv : pvListBoosterVA)
            QObject::connect(pv, &QEpicsPV::valueChanged, this, [this](){
                ui->ledBoosterVA->setValue( std::any_of(pvListBoosterVA.begin(), pvListBoosterVA.begin(), [](QEpicsPV* pv) {
                    return pv->get().toInt() != 0 && pv->get().toInt() != 3;
                }));
            });
        for(QEpicsPV* pv : pvListIMG)
            QObject::connect(pv, &QEpicsPV::valueChanged, this, [this](){ ui->ledIMG->setValue(list_sum(pvListIMG) == 0); });
        for(QEpicsPV* pv : pvListSRFS)
            QObject::connect(pv, &QEpicsPV::valueChanged, this, [this](){ ui->ledSRFS->setValue( contains_any(pvListSRFS, 1) ); });
        for(QEpicsPV* pv : pvListSRTS)
            QObject::connect(pv, &QEpicsPV::valueChanged, this, [this](){ ui->ledSRTS->setValue( contains_any(pvListSRTS, 1) ); });
        for(QEpicsPV* pv : pvTL2Corr)
            QObject::connect(pv, SIGNAL(valueChanged(QVariant)), this, SLOT(allPVsChanged()));
        for(QEpicsPV* pv : pvTL2Quads)
            QObject::connect(pv, SIGNAL(valueChanged(QVariant)), this, SLOT(allPVsChanged()));
        for(QEpicsPV* pv : pvTL2BMX)
            QObject::connect(pv, SIGNAL(valueChanged(QVariant)), this, SLOT(allPVsChanged()));
        for(QEpicsPV* pv : pvTL2Vacuum)
            QObject::connect(pv, &QEpicsPV::valueChanged, this, [this]() { ui->ledTL2Vacuum->setValue( contains_any(pvTL2Vacuum, 1) ); });
        for(QEpicsPV* pv : pvListBPMILK)
            QObject::connect(pv, &QEpicsPV::valueChanged, this, [this]() { ui->ledBPMInterlocks->setValue( contains_any(pvListBPMILK, 1) ); });
        for(QEpicsPV* pv : valve1FaultPVs)
            QObject::connect(pv, SIGNAL(valueChanged(QVariant)), this, SLOT(onValvesStatusChanged()));
        for(QEpicsPV* pv : valve1ClosePVs)
            QObject::connect(pv, SIGNAL(valueChanged(QVariant)), this, SLOT(onValvesStatusChanged()));
        for(QEpicsPV* pv : valve1OpenPVs)
            QObject::connect(pv, SIGNAL(valueChanged(QVariant)), this, SLOT(onValvesStatusChanged()));
        for(QEpicsPV* pv : valve2FaultPVs)
            QObject::connect(pv, SIGNAL(valueChanged(QVariant)), this, SLOT(onValvesStatusChanged()));
        for(QEpicsPV* pv : valve2ClosePVs)
            QObject::connect(pv, SIGNAL(valueChanged(QVariant)), this, SLOT(onValvesStatusChanged()));
        for(QEpicsPV* pv : valve2OpenPVs)
            QObject::connect(pv, SIGNAL(valueChanged(QVariant)), this, SLOT(onValvesStatusChanged()));
        for(QEpicsPV* pv : pvTL2THS) {
            QObject::connect(pv, &QEpicsPV::valueChanged, this, [this]() {
                ui->ledTL2THS->setValue(pvTL2THS[0]->get().toInt() == 1 && pvTL2THS[1]->get().toInt() != 3);
            });
        }

    } while(false);

    this->pvCurrent   = new QEpicsPV("SRC01-DI-DCCT1:getDcctCurrent");
    this->pvEnergy    = new QEpicsPV("SR-DI:getBeamEnergy");
    this->pvCurrentBO = new QEpicsPV("BO-DI-DCCT1:getDcctCurrent");
    this->pvCTR       = new QEpicsPV("SR-DI:getCTR");
    this->pvAGPS      = new QEpicsPV("AGPS:getState");
    this->pvOP        = new QEpicsPV("OP:enable");
    this->pvStatus    = new QEpicsPV("Machine:Status");
    this->pvKick      = new QEpicsPV("SR-PS-INK:getVoltage");
    this->pvCAVMaintenance1 = new QEpicsPV("SRC03-RF-CAV1:isMaintenanceEnabled");
    this->pvCAVMaintenance2 = new QEpicsPV("SRC03-RF-CAV2:isMaintenanceEnabled");
    this->pvCAVMaintenance3 = new QEpicsPV("SRC03-RF-CAV3:isMaintenanceEnabled");
    this->pvCAVMaintenance4 = new QEpicsPV("SRC03-RF-CAV4:isMaintenanceEnabled");
    this->pvSeptumCurrentLimit = new QEpicsPV("INJ-SEP-DCCT-LIM:isInterlock");
    this->pvSeptumMs = new QEpicsPV("INJ-SEP-ID09-GAP:isInterlock");
    this->pvSeptumHeseb = new QEpicsPV("INJ-SEP-UND-GAP:isInterlock");
    this->pvSeptumBeats = new QEpicsPV("INJ-SEP-ID10-GAP:isInterlock");
    this->pvTuneX = new QEpicsPV("SR-RF-MBF-X:getTune");
    this->pvTuneY = new QEpicsPV("SR-RF-MBF-Y:getTune");

    this->pvIRStatus = new QEpicsPV("D02C01-VA-ABS:getStatus.RVAL");
    this->pvXAFSStatus = new QEpicsPV("FE08-VA-PHSH:getStatus.RVAL");
    this->pvMSStatus = new QEpicsPV("I09FE-VA-PSH:getStatus.RVAL");
    this->pvBeatsStatus = new QEpicsPV("I10FE-VA-PSH:getStatus.RVAL");
    this->pvHesebStatus = new QEpicsPV("I11FE-VA-PSH:getStatus.RVAL");
    this->pvMSGap = new QEpicsPV("ID09R01-MC1:I.RBV");
    this->pvBeatsGap = new QEpicsPV("ID10R01-MC1:I.RBV");
    this->pvHesebGap = new QEpicsPV("ID11:getGap");
    this->pvHesebShift = new QEpicsPV("ID11:getShift");

    QString hostname = QHostInfo::localHostName().toLower();
    ui->comMachineStatus->setEnabled(hostname == "control-op0" || hostname == "control-op1" || hostname == "control-op2" || hostname == "control-op3");

    ui->cpCurrentSR->addGraph();
    ui->cpCurrentBO->addGraph();
    ui->cpCTR->addGraph();
    ui->cpCurrentSR->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->cpCurrentBO->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->cpCTR->graph(0)->setLineStyle(QCPGraph::lsLine);

    QSharedPointer<QCPAxisTickerDateTime> ticker(new QCPAxisTickerDateTime);
    ticker->setDateTimeFormat("hh:mm:ss");
    ticker->setTickCount(4);
    ticker->setTickStepStrategy(QCPAxisTicker::tssReadability);
    ui->cpCurrentSR->xAxis->setTicker(ticker);
    ui->cpCurrentBO->xAxis->setTicker(ticker);
    ui->cpCTR->xAxis->setTicker(ticker);

    this->rampingWithRF = true;

    this->pvTimer = new QTimer;
    QObject::connect(pvTimer, SIGNAL(timeout()), this, SLOT(pvTimerTimeout()));
    pvTimer->setInterval(1000);
    pvTimer->start();

    this->psc_warnings = QList<int>({0x32, 0x37, 0x38, 0x46, 0x47, 0x4a});
    ui->lblTuneX->setStyleSheet(LABEL_DEFAULT_QSS);
    ui->lblTuneY->setStyleSheet(LABEL_DEFAULT_QSS);

    QObject::connect(ui->btnBOVacuum, SIGNAL(clicked()), this, SLOT(on_btnBOVA_clicked()));
    QObject::connect(ui->btnSRVacuum_2, SIGNAL(clicked()), this, SLOT(on_btnSRVacuum_clicked()));
    QObject::connect(ui->btnSRRF_2, SIGNAL(clicked()), this, SLOT(on_btnSRRF_clicked()));
    QObject::connect(ui->btnTL1Vacuum_2, SIGNAL(clicked()), this, SLOT(on_btnTL1Vacuum_clicked()));
    QObject::connect(ui->btnTL1Vacuum_3, SIGNAL(clicked()), this, SLOT(on_btnTL1Vacuum_clicked()));
    QObject::connect(ui->btnTL2Vacuum_2, SIGNAL(clicked()), this, SLOT(on_btnTL2Vacuum_clicked()));
    QObject::connect(this->pvOP, SIGNAL(valueChanged(QVariant)), this, SLOT(onTargetChanged()));
    QObject::connect(this->pvStatus, SIGNAL(valueChanged(QVariant)), this, SLOT(onMachineStatusChanged(QVariant)));
    QObject::connect(pvAGPS, SIGNAL(valueChanged(QVariant&)), this, SLOT(onAGPSStateChanged()));
    QObject::connect(ui->cbPlant1, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxesChanged(int)));
    QObject::connect(ui->cbPlant2, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxesChanged(int)));
    QObject::connect(ui->cbPlant3, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxesChanged(int)));
    QObject::connect(ui->cbPlant4, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxesChanged(int)));
    QObject::connect(this->pvCurrent, &QEpicsPV::valueChanged, this, [this](){ this->ui->ledCurrent->setValue(this->pvCurrent->get().toDouble() > 20); });
    QObject::connect(this->pvEnergy, &QEpicsPV::valueChanged, this, [this](){
        double energy = this->pvEnergy->get().toDouble();
        this->ui->ledEnergy->setValue(energy > 2.49);
        this->ui->btnRamp->setEnabled(energy <= 2.49);
        this->ui->btnRampDown->setEnabled(energy > 2.49);
    });
    QObject::connect(this->pvKick, SIGNAL(valueChanged(QVariant)), this, SLOT(onKickValChanged()));
    QObject::connect(this->pvCAVMaintenance1, SIGNAL(valueChanged(QVariant)), this, SLOT(onCAVMaintenanceChanged()));
    QObject::connect(this->pvCAVMaintenance2, SIGNAL(valueChanged(QVariant)), this, SLOT(onCAVMaintenanceChanged()));
    QObject::connect(this->pvCAVMaintenance3, SIGNAL(valueChanged(QVariant)), this, SLOT(onCAVMaintenanceChanged()));
    QObject::connect(this->pvCAVMaintenance4, SIGNAL(valueChanged(QVariant)), this, SLOT(onCAVMaintenanceChanged()));
    QObject::connect(this->pvSeptumCurrentLimit, SIGNAL(valueChanged(QVariant)), this, SLOT(onSeptumInterlock()));
    QObject::connect(this->pvSeptumMs, SIGNAL(valueChanged(QVariant)), this, SLOT(onSeptumInterlock()));
    QObject::connect(this->pvSeptumHeseb, SIGNAL(valueChanged(QVariant)), this, SLOT(onSeptumInterlock()));
    QObject::connect(this->pvSeptumBeats, SIGNAL(valueChanged(QVariant)), this, SLOT(onSeptumInterlock()));
    QObject::connect(this->pvTuneX, SIGNAL(valueChanged(QVariant)), this, SLOT(onTuneXChanged()));
    QObject::connect(this->pvTuneY, SIGNAL(valueChanged(QVariant)), this, SLOT(onTuneYChanged()));

//    QObject::connect(this->pvIRStatus, SIGNAL(valueChanged(QVariant)), this, SLOT(txtIRStatus()));
//    QObject::connect(this->pvXAFSStatus, SIGNAL(valueChanged(QVariant)), this, SLOT(txtXAFSStatus()));
//    QObject::connect(this->pvMSStatus, SIGNAL(valueChanged(QVariant)), this, SLOT(txtMSStatus()));
//    QObject::connect(this->pvBeatsStatus, SIGNAL(valueChanged(QVariant)), this, SLOT(txtBeatsStatus()));
//    QObject::connect(this->pvHesebStatus, SIGNAL(valueChanged(QVariant)), this, SLOT(txtHesebStatus()));
//    QObject::connect(this->pvMSGap, SIGNAL(valueChanged(QVariant)), this, SLOT(txtMSGap()));
//    QObject::connect(this->pvBeatsGap, SIGNAL(valueChanged(QVariant)), this, SLOT(txtBeatsGap()));
//    QObject::connect(this->pvHesebGap, SIGNAL(valueChanged(QVariant)), this, SLOT(txtHesebGap()));




    this->message    = NULL;
    this->boRF       = NULL;
    this->bmDetails  = NULL;
    this->gauges     = NULL;
    this->ionPumps   = NULL;
    this->tl1Vacuum  = NULL;
    this->mainPower  = NULL;
    this->boCool     = NULL;
    this->boVac      = NULL;
    this->rf         = NULL;
    this->boosterPS  = NULL;
    this->boosterDI  = NULL;
    this->tl2Vacuum  = NULL;
    this->tl1Power   = NULL;
    this->tl2Power   = NULL;
    this->tl2Diag    = NULL;
    this->tl2Cooling = NULL;
    this->sequencer  = NULL;
    this->srPS       = NULL;
    this->boRF       = NULL;
    this->beamlines  = NULL;
    this->mps        = NULL;
    this->dcct       = NULL;
    this->monitors   = NULL;
    this->wiggler09  = NULL;
    this->profiles   = NULL;
    this->srDI       = NULL;
    this->mi         = NULL;
    this->coils      = NULL;
    this->motors     = NULL;
    this->valves     = NULL;
    this->microtronAnalog = NULL;
    this->srVacuum = NULL;
    this->cooling = NULL;
    this->eff = NULL;
    this->ffStatus = NULL;
    this->bpmConfig = NULL;
    this->beamlinesShutters = NULL;
    this->radiationMonitors = NULL;
}

FormInjection::~FormInjection()
{
    delete ui;
}

void FormInjection::on_btnTimingOFF_clicked()
{
    Client::writePV("GBL-TI-EVR0-P1:enable", 0);
    Client::writePV("GBL-TI-EVR0-P2:enable", 0);
    Client::writePV("GBL-TI-EVR0-P3:enable", 0);
}

void FormInjection::on_btnTimingON_clicked()
{
    Client::writePV("GBL-TI-EVR0-P1:enable", 1);
    Client::writePV("GBL-TI-EVR0-P2:enable", 1);
    Client::writePV("GBL-TI-EVR0-P3:enable", 1);
}

void FormInjection::on_btnBORF_clicked() { OPEN_UI(this->boRF, uiBORFMain, this); }

void FormInjection::on_btnBeamlines_clicked() { OPEN_UI(this->beamlines, FormBeamlines, this); }

void FormInjection::on_btnMPS_clicked() { OPEN_UI(this->mps, FormMPS, this); }

void FormInjection::on_btnDCCT_clicked() { OPEN_UI(this->dcct, FormDCCT, this); }

void FormInjection::on_btnMonitors_clicked() { OPEN_UI(this->monitors, FormRadiationMonitors, this); }

void FormInjection::on_btnSRRF_clicked() { OPEN_UI(this->rf, uiSR_RF, this); }

void FormInjection::allPVsChanged()
{
    if(std::any_of(std::begin(pvListsMap["pvListHC"]), std::end(pvListsMap["pvListHC"]), [this](QEpicsPV* pv){ int error = (pv->get().toInt() & 0xFF); return error != 0 && !psc_warnings.contains(error); })) {
        ui->ledHC->setValue(2);
    }
    else if(std::any_of(std::begin(pvListsMap["pvListHC"]), std::end(pvListsMap["pvListHC"]), [this](QEpicsPV* pv){ return psc_warnings.contains(pv->get().toInt() & 0xFF); })) {
        ui->ledHC->setValue(1);
    }
    else
        ui->ledHC->setValue(0);

    if(std::all_of(std::begin(pvListVC), std::end(pvListVC), [this](QEpicsPV* pv){ int error = (pv->get().toInt() & 0xFF); return error != 0 && !psc_warnings.contains(error);  })) {
        ui->ledVC->setValue(2);
    }
    else if(std::any_of(std::begin(pvListVC), std::end(pvListVC), [this](QEpicsPV* pv){ return psc_warnings.contains(pv->get().toInt() & 0xFF); })) {
        ui->ledVC->setValue(1);
    }
    else
        ui->ledVC->setValue(0);

    if(std::any_of(std::begin(pvListSQ), std::end(pvListSQ), [this](QEpicsPV* pv){ int error = (pv->get().toInt() & 0xFF); return error != 0 && !psc_warnings.contains(error);  })) {
        ui->ledSQ->setValue(2);
    }
    else if(std::any_of(std::begin(pvListSQ), std::end(pvListSQ), [this](QEpicsPV* pv){ return psc_warnings.contains(pv->get().toInt() & 0xFF); })) {
        ui->ledSQ->setValue(1);
    }
    else
        ui->ledSQ->setValue(0);

    // State:TL2:CR
    ui->ledTL2Corr->setValue(1);
    iterate_for(pv, pvTL2Corr) {
        // Throwing out some c++ iterators magic ......
        // De-referencing the current and next iterators.
        if((*pv)->get().toInt() != 1 || (*(++pv))->get().toInt() == 3) {
            ui->ledTL2Corr->setValue(0);
            break;
        }
    }

    // State:TL2:Q
    ui->ledTL2Quads->setValue(1);
    iterate_for(pv, pvTL2Quads) {
        if((*pv)->get().toInt() != 1 || (*(++pv))->get().toInt() == 3) {
            ui->ledTL2Quads->setValue(0);
            break;
        }
    }

    // State:TL2:BM
    ui->ledTL2BMX->setValue(1);
    iterate_for(pv, pvTL2BMX) {
        if((*pv)->get().toInt() != 1 || (*(++pv))->get().toInt() == 3) {
            ui->ledTL2BMX->setValue(0);
            break;
        }
    }

    int count = list_sum(pvListBPM);
    if(count == 48)
        ui->ledILK->setValue(0);
    else if(count < 48 && count > 0)
        ui->ledILK->setValue(1);
    else
        ui->ledILK->setValue(2);
}

void FormInjection::on_btnD09W_clicked() { OPEN_UI(this->wiggler09, FormWigglerC09, this); }

void FormInjection::on_btnSRPS_clicked() { OPEN_UI(this->srPS, RingPowerSupplyWindow, this); }

void FormInjection::on_btnCorrectors_clicked() { OPEN_UI(this->crPS, RingCorrectorsWindow, this); }

void FormInjection::on_btnSRVacuum_clicked() { OPEN_UI(this->srVacuum, RingVacuumWindow, this); }

void FormInjection::on_btnValves_clicked() { OPEN_UI(this->valves, ValvesWindow, this); }

void FormInjection::on_btnSRCooling_clicked() { OPEN_UI(this->cooling, RingCoolingWindow, this); }

void FormInjection::on_btnBOVA_clicked() { OPEN_UI(this->boVac, uiBOVacuum, this); }

void FormInjection::on_btnBOCO_clicked() { OPEN_UI(this->boCool, uiBOCooling, this); }

void FormInjection::on_pushButton_clicked()
{
    QProcess* p = new QProcess;
    p->start("gnome-terminal", {
                 "--geometry", "100x30",
                 "-x", "python3", "/home/control/nfs/groups/accelerator-physics/matlab_screepts/correct_coupling.py"
             });
}

void FormInjection::on_pushButton_2_clicked()
{
    QProcess* p = new QProcess;
    p->start("gnome-terminal", {
                 "--geometry", "100x30",
                 "-x", "python3", "/home/control/nfs/groups/accelerator-physics/matlab_screepts/correct_optics.py"
             });
}

void FormInjection::on_btnCycle_clicked()
{
    QProcess* p = new QProcess;
    p->setWorkingDirectory(getenv("HOME"));
    p->start("gnome-terminal", {"--geometry", "100x30", "-x", "python3", "bin/Cycle_Magnets.py"});
}

void FormInjection::on_btnRamp_clicked()
{
    QProcess* p = new QProcess;
    p->setWorkingDirectory(getenv("HOME"));
    p->start("gnome-terminal", {"--geometry", "100x30", "-x", "python3",
                                "bin/PS_Ramping.py", "--file", "/home/control/nfs/machine/waveforms/Storage_Ring/currents_rampup.yaml"});

    if (this->rampingWithRF)
    {
        QProcess* p2 = new QProcess;
        p2->setWorkingDirectory("/home/control/nfs/groups/accelerator-physics/matlab_screepts");
        p2->start("gnome-terminal",  {
                      "--geometry", "100x30",
                      "-x",         "/home/control/nfs/groups/accelerator-physics/matlab_screepts/rf_ramp_test.sh"
                  });
    }
}

void FormInjection::rfRampUpdate()
{
//    int h = 222;
//    double alpha = 0.008;
//    double nyu = 0.012800;
//    double energy = this->pvEnergy->get().toDouble();
//    double current = this->pvCurrent->get().toDouble();
//    double rampRate = 0.25;

//    // energy_loss=8.85e-5*energy^4/5.95643
//    double energyLoss = (8.85E-5 * qPow(energy, 4)) / 5.95643;

//    // c(1)=h^2*alpha^2/(4*pi^2*energy^2); c(2)=energy_loss^2*c(1)+nyu_s^4;
//    double c1 = pow(h, 2) * pow(alpha, 2) / (4 * pow(M_PI, 2) * pow(energy, 2));
//    double c2 = pow(energyLoss, 2) * c1 + pow(nyu, 4);

//    // voltage=sqrt(c(2)/c(1))/4*1e6;
//    double voltage = sqrt(c2 / c1) / 4 * 1E6;

//    QString pv;
//    if(energy >= 0.75 && energy <= 2.5 && current > 0.5) {
//        if(voltage >= 168) {
//            for(int lle = 1; lle <= 2; lle++)
//            {
//                for(int board = 1; board <= 2; board++)
//                {
//                    pv = QString("LLE%1:BRD%2:").arg(lle).arg(board);
//                    Client::writePV(pv + "RAMP:TRIGEN", "Int");
//                    Client::writePV(pv + "RAMP:MODE", "CW");
//                    Client::writePV(pv + "RAMP:LENGTH", 10);
//                    Client::writePV(pv + "RAMP:AMPRATE", rampRate);
//                    Client::writePV(pv + "RAMP:ASTART", voltage);
//                    Client::writePV(pv + "RAMP:AEND", voltage);
//                    Client::writePV(pv + "RAMP:LOAD", 1);
//                }
//            }
//        }
//    }
//    else
//        this->rfRampTimer->stop();
}

void FormInjection::on_btnProfiles_clicked() { OPEN_UI(this->profiles, FormProfiles, this); }

void FormInjection::on_btnSRDiagnostics_clicked() { OPEN_UI(this->bpmConfig, FormBpmConfig, this); }

void FormInjection::onComboBoxesChanged(int index)
{
    QEComboBox* box = (QEComboBox*) sender();
    QString name = box->objectName();
    int id = name[name.length() - 1].toLatin1() - 0x30;
    if(index==1){
        uiSR_RFCurrent* rf= new uiSR_RFCurrent(0,QString::number(id));
        showUI(rf);
    }
    else if(index==2){
        uiSR_RFTempratures* rf_Temp= new uiSR_RFTempratures(id);
        showUI(rf_Temp);
    }
    else if(index==3){
        uiSR_RFInterlocks* rf_Interlocks= new uiSR_RFInterlocks(0,QString::number(id));
        showUI(rf_Interlocks);
    }
    else if(index==4){
        uiSR_RFRectifiers* rf_Rectifiers= new uiSR_RFRectifiers(0,QString::number(id));
        showUI(rf_Rectifiers);
    }

    box->setCurrentIndex(0);
    return;
}

void FormInjection::on_btnMIOperation_clicked() { OPEN_UI(this->mi, uiMicrotron, this); }

void FormInjection::on_btnMicrotronMotors_clicked() { OPEN_UI(this->motors, FormMotors, this); }

void FormInjection::on_btnMicrotronPS_clicked() { OPEN_UI(this->coils, MicrotronCoilsWindow, this); }

void FormInjection::onTargetChanged() { ui->btnEnable->setEnabled(this->pvOP->get().toInt() == 0); }

void FormInjection::pvTimerTimeout()
{
    uint elapsed = QDateTime::currentDateTime().toTime_t();
    static int x = 0;
    if(x++ >= PLOT_BUFFER)
    {
        ui->cpCurrentSR->graph(0)->data()->remove(ui->cpCurrentSR->graph(0)->data()->at(0)->key);
        ui->cpCurrentBO->graph(0)->data()->remove(ui->cpCurrentBO->graph(0)->data()->at(0)->key);
        ui->cpCTR->graph(0)->data()->remove(ui->cpCTR->graph(0)->data()->at(0)->key);
    }

    ui->cpCurrentSR->graph(0)->addData(elapsed, pvCurrent->get().toDouble());
    ui->cpCurrentSR->graph(0)->keyAxis()->rescale();
    ui->cpCurrentSR->graph(0)->valueAxis()->rescale();
    ui->cpCurrentSR->replot();

    ui->cpCurrentBO->graph(0)->addData(elapsed, pvCurrentBO->get().toDouble());
    ui->cpCurrentBO->graph(0)->keyAxis()->rescale();
    ui->cpCurrentBO->graph(0)->valueAxis()->rescale();
    ui->cpCurrentBO->replot();

    if(pvCTR->get().toDouble() >= 100.0)
        ui->cpCTR->graph(0)->addData(elapsed, 100);
    else
        ui->cpCTR->graph(0)->addData(elapsed, pvCTR->get().toDouble());
    ui->cpCTR->graph(0)->keyAxis()->rescale();
    ui->cpCTR->graph(0)->valueAxis()->rescale();
    ui->cpCTR->replot();
}

void FormInjection::on_pushButton_3_clicked()
{
    QWidgetList list = QApplication::topLevelWidgets();
    foreach (QWidget* w, list) {
        if(w->windowTitle() == QString(TITLE_MAIN))
        {
            w->raise();
            break;
        }
    }
}

void FormInjection::on_btnMessage_clicked() { OPEN_UI(this->message, FormMessage, this); }

void FormInjection::on_btnDetailsBM_clicked() { OPEN_UI(this->bmDetails, uiSRPowerSupplyDetails, "SR-PS-BM", this); }

void FormInjection::on_btnSeptumON_clicked()
{
    Client::writePV("SR-PS-INS:enableTrigger", 1);
    Client::writePV("SR-PS-INS:sequenceFeedback.PROC", 1);
    Client::writePV("SR-PS-INS:sequenceSetpoint.PROC", 1);
}

void FormInjection::on_btnSeptumOFF_clicked()
{
    Client::writePV("SR-PS-INS:disableTrigger", 1);
    Client::writePV("SR-PS-INS:getPID.FBON", 0);
    Client::writePV("SR-PS-INS:setVoltage", 0);
}

void FormInjection::on_btnGauges_clicked() { OPEN_UI(this->gauges, FormGauges, this); }

void FormInjection::on_btnTL1Vacuum_clicked() { OPEN_UI(this->tl1Vacuum, uiTL1Vacuum, this); }

void FormInjection::on_btnMainPower_clicked() { OPEN_UI(this->mainPower, FormMainPower, this); }

void FormInjection::onAGPSStateChanged()
{
    int value = this->pvAGPS->get().toInt();
    if(value == 0)
    {
        ui->ledPowerAGPS->setValue(0);
    }
    else if(value == 1 || value == 2)
    {
        ui->ledPowerAGPS->setValue(2);
    }
    else if(value == 3)
    {
        ui->ledPowerAGPS->setValue(1);
    }
    else if(value == 4)
    {
        ui->ledPowerAGPS->setValue(1);
    }
    else if(value == 20)
    {
        ui->ledPowerAGPS->setValue(3);
    }
    else
    {
        ui->ledPowerAGPS->setValue(0);
    }
}

void FormInjection::onValvesStatusChanged()
{
    QSimpleShape* led;
    for(int i = 0; i < 10; i++)
    {
        led = this->findChild<QSimpleShape*>(QString("valve1Status_%1").arg(i+1));

        if(this->valve1FaultPVs[i]->get().toBool())
            led->setValue(0);
        else if(this->valve1ClosePVs[i]->get().toBool())
            led->setValue(1);
        else if(this->valve1OpenPVs[i]->get().toBool())
            led->setValue(2);
        else
            led->setValue(3);

        if(i < 8) {
            led = this->findChild<QSimpleShape*>(QString("valve2Status_%1").arg(i+1));

            if(this->valve2FaultPVs[i]->get().toBool())
                led->setValue(0);
            else if(this->valve2ClosePVs[i]->get().toBool())
                led->setValue(1);
            else if(this->valve2OpenPVs[i]->get().toBool())
                led->setValue(2);
            else
                led->setValue(3);
        }
    }
}

void FormInjection::on_btnIonPumps_clicked() { OPEN_UI(this->ionPumps, IonPumpsWindow, this); }

void FormInjection::on_btnBOPower_clicked() { OPEN_UI(this->boosterPS, FormBoosterPS, this); }

void FormInjection::on_btnBODiag_clicked() { OPEN_UI(this->boosterDI, FormBoosterDI, this); }

void FormInjection::on_btnTL2Vacuum_clicked() { OPEN_UI(this->tl2Vacuum, uiTL2Vacuum, this); }

void FormInjection::on_btnTL1Power_clicked() { OPEN_UI(this->tl1Power, TL1CorrectorsWindow, this); }

void FormInjection::on_btnTL2PowerSupplies_clicked() { OPEN_UI(this->tl2Power, uiTL2PowerSupply, this); }

void FormInjection::on_btnTL2Diagnostics_clicked() { OPEN_UI(this->tl2Diag, uiTL2Diagnostics, this); }

void FormInjection::on_btnTL2Cooling_clicked() { OPEN_UI(this->tl2Cooling, uiTL2Cooling, this); }

void FormInjection::on_btnSequencer_clicked() { OPEN_UI(this->sequencer, MicrotronTriggerWindow, this); }

void FormInjection::onMachineStatusChanged(QVariant value)
{
    bool enabled;

    enabled = value.toInt() != 3 && value.toInt() != 6 && value.toInt() != 7;
    ui->btnRamp->setEnabled(enabled);
    ui->btnCycle->setEnabled(enabled);
    ui->btnInjKickerTrigOn->setEnabled(enabled);
    ui->txtDipoleCurrent->setEnabled(enabled);
    ui->btnRampDown->setEnabled(enabled);
}

void FormInjection::on_btnBORF_2_clicked()
{
    OPEN_UI(this->boRF,uiBORFMain,this);
}

void FormInjection::onKickValChanged()
{
    double kickVal = this->pvKick->get().toDouble();
    double val;
    val = (0.2578 * kickVal)/1000;
    QString strKickVal = QString::number(val, 'f', 5) + " mrad";
    ui->lblKick->setText(strKickVal);
}

void FormInjection::on_btnMicrotronTemps_clicked()
{
    OPEN_UI(this->microtronAnalog, uiMicrotronAnalog, this);
}


void FormInjection::on_comMachineStatus_activated(int index)
{
    QMessageBox::StandardButton reply = QMessageBox::question(nullptr, "Confirmation", "The machine status will be changed, are you sure?", QMessageBox::Yes|QMessageBox::No);

//    if(reply == QMessageBox::Yes) {
//        Client::writePV("Machine:Status", index);
//    }

    if (index == 0 && reply == QMessageBox::Yes){
        Client::writePV("Machine:Status",0);
    }
    else if (index == 1 && reply == QMessageBox::Yes) {
        Client::writePV("Machine:Status",1);
    }
    else if (index == 2 && reply == QMessageBox::Yes) {
        Client::writePV("Machine:Status",2);
    }
    else if (index == 3 && reply == QMessageBox::Yes) {
        Client::writePV("Machine:Status",3);
    }
    else if (index == 4 && reply == QMessageBox::Yes) {
        Client::writePV("Machine:Status",4);
    }
    else if (index == 5 && reply == QMessageBox::Yes) {
        Client::writePV("Machine:Status",5);
    }
    else if (index == 6 && reply == QMessageBox::Yes) {
        Client::writePV("Machine:Status",6);
    }
    else if (index == 7 && reply == QMessageBox::Yes) {
        Client::writePV("Machine:Status",7);
    }
    else if (index == 8 && reply == QMessageBox::Yes) {
        Client::writePV("Machine:Status",8);

    }
}

void FormInjection::onCAVMaintenanceChanged(){
    int Cav1 = this->pvCAVMaintenance1->get().toInt();
    int Cav2 = this->pvCAVMaintenance2->get().toInt();
    int Cav3 = this->pvCAVMaintenance3->get().toInt();
    int Cav4 = this->pvCAVMaintenance4->get().toInt();

    if (Cav1 == 1 || Cav2 == 1 || Cav3 == 1 || Cav4 == 1)
    {
        ui->lblRfMaintenanceMode->setText("Enabled");
        ui->lblRfMaintenanceMode->setStyleSheet("color : red;");
    }
    else
    {
        ui->lblRfMaintenanceMode->setText("Disabled");
        ui->lblRfMaintenanceMode->setStyleSheet("color : green;");
    }
}

void FormInjection::on_btnCurrentLimit_clicked()
{
    QString goldenHash = "16a57ae8604448473034baf5056c17a42f1d4771ac1a0927e687e7524595dd21";
    FormPassword * authObj = new FormPassword(goldenHash, this);
    QObject::connect(authObj, SIGNAL(authenticated()), this, SLOT(open_current_limit()));

    if (!FormPassword::dialogOpen) {
        authObj->show();
        FormPassword::dialogOpen = true;
    }
//    open_current_limit();
}

void FormInjection::open_current_limit()
{
    FormCurrentLimit* setCurrent = new FormCurrentLimit(this);
    setCurrent->show();
}

void FormInjection::on_btnSeptumInterlocks_clicked()
{
    FormSeptumInterlocks* septum_interlocks = new FormSeptumInterlocks(this);
    septum_interlocks->show();
}

void FormInjection::onSeptumInterlock(){
    int ms_interlock = this->pvSeptumMs->get().toInt();
    int beats_interlock = this->pvSeptumBeats->get().toInt();
    int heseb_interlock = this->pvSeptumHeseb->get().toInt();
    int current_limit_interlock = this->pvSeptumCurrentLimit->get().toInt();

    if (ms_interlock == 0 || beats_interlock == 0 || heseb_interlock == 0 || current_limit_interlock == 0)
    {
        ui->ledSeptumInterlocks->setValue(0);
    }
    else
    {
        ui->ledSeptumInterlocks->setValue(1);

    }
}

void FormInjection::on_btnBeamlinesInterlocks_clicked()
{
    FormBeamlinesInterlocks* beamlines_interlocks = new FormBeamlinesInterlocks(this);
    beamlines_interlocks->show();
}

void FormInjection::on_btnEff_clicked()
{
    OPEN_UI(this->eff, FormInjectionEfficiency, this);
}

void FormInjection::on_btnFFStatus_clicked()
{
    OPEN_UI(this->ffStatus, FormFeedforwardStatus, this);
}

void FormInjection::on_btnControlExpert_clicked()
{
    QString goldenHash = "a665a45920422f9d417e4867efdc4fb8a04a1f3fff1fa07e998e86f7f7a27ae3";
    FormPassword * authObj = new FormPassword(goldenHash, this);
    QObject::connect(authObj, SIGNAL(authenticated()), this, SLOT(open_control_expert()));

    if (!FormPassword::dialogOpen) {
        authObj->show();
        FormPassword::dialogOpen = true;
    }
}

void FormInjection::open_control_expert()
{
    FormControlExpert* controlExpert = new FormControlExpert(this);
    controlExpert->show();
}

void FormInjection::on_btnSRDiagnostics_2_clicked()
{
    OPEN_UI(this->srDI, FormDiagnostics, this);
}

void FormInjection::on_btnBeamlinesShutters_clicked()
{
    OPEN_UI(this->beamlinesShutters, FormBeamlinesStatus, this);
}



//void FormInjection::txtIRStatus()
//{
//    int status = this->pvIRStatus->get().toInt();
//    if(status == 1)
//    {
//        this->ui->txtIRStatus->setStyleSheet("background-color:#F0AD4E;");
//    }
//    else
//    {
//        this->ui->txtIRStatus->setStyleSheet("background-color:#5CB85C;");
//    }
//}

//void FormInjection::txtXAFSStatus()
//{
//    int status = this->pvXAFSStatus->get().toInt();
//    if(status == 1)
//    {
//        this->ui->txtXAFSStatus->setStyleSheet("background-color:#F0AD4E;");
//    }
//    else
//    {
//        this->ui->txtXAFSStatus->setStyleSheet("background-color:#5CB85C;");
//    }
//}

//void FormInjection::txtMSStatus()
//{
//    int status = this->pvMSStatus->get().toInt();
//    if(status == 1)
//    {
//        this->ui->txtMSStatus->setStyleSheet("background-color:#F0AD4E;");
//    }
//    else
//    {
//        this->ui->txtMSStatus->setStyleSheet("background-color:#5CB85C;");
//    }
//}

//void FormInjection::txtMSGap()
//{
//    double gap = this->pvMSGap->get().toDouble();
//    if(gap <= 12.500)
//    {
//        this->ui->txtMSGap->setStyleSheet("background-color:#5CB85C;");
//    }
//    else
//    {
//        this->ui->txtMSGap->setStyleSheet("background-color:#F0AD4E;");
//    }
//}


//void FormInjection::txtBeatsStatus()
//{
//    int status = this->pvBeatsStatus->get().toInt();
//    if(status == 1)
//    {
//        this->ui->txtBeatsStatus->setStyleSheet("background-color:#F0AD4E;");
//    }
//    else
//    {
//        this->ui->txtBeatsStatus->setStyleSheet("background-color:#5CB85C;");
//    }
//}

//void FormInjection::txtBeatsGap()
//{
//    double gap = this->pvBeatsGap->get().toDouble();
//    if(gap <= 30.500)
//    {
//        this->ui->txtBeatsGap->setStyleSheet("background-color:#5CB85C;");
//    }
//    else
//    {
//        this->ui->txtBeatsGap->setStyleSheet("background-color:#F0AD4E;");
//    }
//}

//void FormInjection::txtHesebStatus()
//{
//    int status = this->pvHesebStatus->get().toInt();
//    if(status == 1)
//    {
//        this->ui->txtHesebStatus->setStyleSheet("background-color:#F0AD4E;");
//    }
//    else
//    {
//        this->ui->txtHesebStatus->setStyleSheet("background-color:#5CB85C;");
//    }
//}

//void FormInjection::txtHesebGap()
//{
//    double gap = this->pvHesebGap->get().toDouble();
//    if(gap <= 36)
//    {
//        this->ui->txtHesebGap->setStyleSheet("background-color:#5CB85C;");
//    }
//    else
//    {
//        this->ui->txtHesebGap->setStyleSheet("background-color:#F0AD4E;");
//    }
//}



void FormInjection::onTuneXChanged()
{
    try {
        double tuneX = this->pvTuneX->get().toDouble();
        this->ui->lblTuneX->setText(QString::number(tuneX+7));


    }  catch (const std::exception& ex) {
        this->ui->lblTuneX->setText("NaN");
    }

}

void FormInjection::onTuneYChanged()
{
    try {
        double tuneY = this->pvTuneY->get().toDouble();
        this->ui->lblTuneY->setText(QString::number(tuneY+6));
    }
    catch (const std::exception& ex) {
        this->ui->lblTuneY->setText("NaN");
    }
}

void FormInjection::on_chkBoxIncludeRf_clicked(bool checked)
{
    this->rampingWithRF = checked;
}

void FormInjection::on_btnRadiationMonitors_clicked()
{
    OPEN_UI(this->radiationMonitors, FormRadiationMonitors, this);
}

void FormInjection::on_btnRampDown_clicked()
{
    QProcess* p = new QProcess;
    p->setWorkingDirectory(getenv("HOME"));
    p->start("gnome-terminal", {"--geometry", "100x30", "-x", "python3",
                                "bin/PS_Ramping.py", "--file", "/home/control/nfs/machine/waveforms/Storage_Ring/currents_rampdown.yaml"});

    if (this->rampingWithRF)
    {
        QProcess* p2 = new QProcess;
        p2->setWorkingDirectory("/home/control/nfs/groups/accelerator-physics/matlab_screepts");
        p2->start("gnome-terminal",  {
                      "--geometry", "100x30",
                      "-x",         "/home/control/nfs/groups/accelerator-physics/matlab_screepts/rf_ramp_test.sh"
                  });
    }

    p = new QProcess;
    p->setWorkingDirectory(getenv("HOME"));
    p->start("/home/control/qt-client/scripts/python_manager.py",  {"-stop", "MS-FeedforwardCorrection"});

    p = new QProcess;
    p->setWorkingDirectory(getenv("HOME"));
    p->start("/home/control/qt-client/scripts/python_manager.py",  {"-stop", "HESEB-FeedforwardCorrection"});

    p = new QProcess;
    p->setWorkingDirectory(getenv("HOME"));
    p->start("/home/control/qt-client/scripts/python_manager.py",  {"-stop", "BEATS-FeedforwardCorrection"});

    QVector<int> indices = {1,3,5,7,9,11,13,15};
    for (auto i : indices) {
        Client::writePV(QString::asprintf("SRC%02d-PS-SQ1:setReference", i), 0);
    }
}
