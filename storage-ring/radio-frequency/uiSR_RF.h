#ifndef UISR_RF_H
#define UISR_RF_H

#include <QMainWindow>
#include <qepicspv.h>
#include <cmath>
#include "storage-ring/radio-frequency/uiSR_RFTempratures.h"
#include "storage-ring/radio-frequency/uiSR_RFInterlocks.h"
#include "storage-ring/radio-frequency/uiSR_RFRectifiers.h"
#include "storage-ring/radio-frequency/uiSR_RFCurrent.h"
#include "storage-ring/radio-frequency/uiSR_RFCoolingRacks.h"
#include "storage-ring/radio-frequency/FormMasterOscillator.h"
#include "storage-ring/radio-frequency/FormLLEInterlocks.h"
#include "storage-ring/radio-frequency/FormTMBFAmplifier.h"
#include "storage-ring/radio-frequency/FormAmplifierExpert.h"
#include "storage-ring/radio-frequency/FromFrontEndBBB.h"
#include "storage-ring/radio-frequency/FormRFCooling.h"
#include "storage-ring/radio-frequency/FormRFDiagnostics.h"
#include "storage-ring/radio-frequency/FormPlungerMotors.h"
#include "galil/FormGalilController.h"

#include "macros.h"

namespace Ui {
class uiSR_RF;
}

class uiSR_RF : public QMainWindow
{
    Q_OBJECT

public:
    explicit uiSR_RF(QWidget *parent = 0);
    ~uiSR_RF();

private slots:
    void on_btnCoolingRacks_clicked();

    void on_btnMO_clicked();

    void on_btnInterlocks_clicked();

    void on_btnAmp_clicked();

    void detailsButtonsClicked();

    void on_btnFrontEnd_clicked();

    void on_qepushbutton_3_clicked();

    void on_btnCooling_clicked();

    void on_pushButton_clicked();

    void plunger_gui_selector(int index);

private:
    Ui::uiSR_RF *ui;
    uiSR_RFCoolingRacks*  CoolingRacks;
    FormMasterOscillator* mo;
    FormLLEInterlocks*    lle;
    FormTMBFAmplifier*    amp;
    FormAmplifierExpert*  expert;
    FormFrontEndBBB*      frontEnd;
    FormRFCooling*        cooling;
    FormRFDiagnostics*    diag;
    FormPlungerMotors*    PlungerMotors;
    FormGalilController* galil;

    QEpicsPV* lleMag[4];
};

#endif // UISR_RF_H
