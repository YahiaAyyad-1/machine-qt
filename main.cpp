#include "mainscreen.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMainWindow* w;
    if(argv[1] && QString(argv[1]) == "mi-trigger")
        w = new MicrotronTriggerWindow;
    else if(argv[1] && QString(argv[1]) == "mi")
        w = new uiMicrotron;
    else if(argv[1] && QString(argv[1]) == "mi-ps")
        w = new MicrotronCoilsWindow;
    else if(argv[1] && QString(argv[1]) == "mi-temp")
        w = new uiMicrotronAnalog;
    else if(argv[1] && QString(argv[1]) == "tl1-ps")
        w = new TL1CorrectorsWindow;
    else if(argv[1] && QString(argv[1]) == "tl1-va")
        w = new uiTL1Vacuum;
    else if(argv[1] && QString(argv[1]) == "bo-va")
        w = new uiBOVacuum;
    else if(argv[1] && QString(argv[1]) == "bo-co")
        w = new uiBOCooling;
    else if(argv[1] && QString(argv[1]) == "bo-rf")
        w = new uiBORFMain;
    else if(argv[1] && QString(argv[1]) == "tl2-ps")
        w = new uiTL2PowerSupply;
    else if(argv[1] && QString(argv[1]) == "tl2-va")
        w = new uiTL2Vacuum;
    else if(argv[1] && QString(argv[1]) == "tl2-di")
        w = new uiTL2Diagnostics;
    else if(argv[1] && QString(argv[1]) == "tl2-co")
        w = new uiTL2Cooling;
    else if(argv[1] && QString(argv[1]) == "sr-va")
        w = new RingVacuumWindow;
    else if(argv[1] && QString(argv[1]) == "sr-ps")
        w = new RingPowerSupplyWindow;
    else if(argv[1] && QString(argv[1]) == "sr-rf")
        w = new uiSR_RF;
    else if(argv[1] && QString(argv[1]) == "sr-co")
        w = new RingCoolingWindow;
    else if(argv[1] && QString(argv[1]) == "evg")
        w = new uiTSEventGenerator;
    else if(argv[1] && QString(argv[1]) == "evr1")
        w = new EventReceiverWindow(0);
    else if(argv[1] && QString(argv[1]) == "evr2")
        w = new EventReceiverWindow(1);
    else if(argv[1] && QString(argv[1]) == "op-message")
        w = new FormMessage;
    else if(argv[1] && QString(argv[1]) == "id11-ps")
        w = new FormUndulatorC11;
    else if(argv[1] && QString(argv[1]) == "id10")
        w = new Form3pwiggler;
    else if(argv[1] && QString(argv[1]) == "id09")
        w = new FormWigglerC09;
    else if(argv[1] && QString(argv[1]) == "inj")
        w = new FormInjection;
    else if(argv[1] && QString(argv[1]) == "mps")
        w = new FormMPS;
    else if(argv[1] && QString(argv[1]) == "di-lib")
        w = new FormSRLiberaMain;
    else if(argv[1] && QString(argv[1]) == "ps-cor")
        w = new RingCorrectorsWindow;
    else if(argv[1] && QString(argv[1]) == "rf-co")
        w = new FormRFCooling;
    else if(argv[1] && QString(argv[1]) == "ps-pp")
        w = new FormMainPower;
    else if(argv[1] && QString(argv[1]) == "co-ha")
        w = new HeatAbsorbersWindow;
    else
        w = new MainScreen;

    w->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, w->size(), QGuiApplication::primaryScreen()->geometry()));
    w->show();
    return a.exec();
}
