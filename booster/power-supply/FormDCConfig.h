#ifndef FORMDCCONFIG_H
#define FORMDCCONFIG_H

#include <QMainWindow>

#include <qepicspv.h>
#include "client.h"

#include "FormDCWaveform.h"
#include "FormTunePI.h"

namespace Ui {
class FormDCConfig;
}

class FormDCConfig : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormDCConfig(QWidget *parent = 0);
    ~FormDCConfig();

private slots:
    void powerInterlocks_Changed();

    void on_cbBMMask_currentIndexChanged(int index);

    void on_cbQFMask_currentIndexChanged(int index);

    void on_cbQDMask_currentIndexChanged(int index);

    void on_comboBox_currentIndexChanged(int index);

    void on_cbTuning_currentIndexChanged(int index);

private:
    Ui::FormDCConfig *ui;

    FormDCWaveform* dcWF;
    FormTunePI* tune;

    QEpicsPV* pvBMInterlocks1;
    QEpicsPV* pvBMInterlocks2;
    QEpicsPV* pvBMInterlocks3;
    QEpicsPV* pvBMInterlocks4;
    QEpicsPV* pvBMInterlocks5;
    QEpicsPV* pvBMInterlocks6;
    QEpicsPV* pvBMInterlocks7;
    QEpicsPV* pvQFInterlocks1;
    QEpicsPV* pvQFInterlocks2;
    QEpicsPV* pvQFInterlocks3;
    QEpicsPV* pvQDInterlocks1;
    QEpicsPV* pvQDInterlocks2;
    QEpicsPV* pvQDInterlocks3;
};

#endif // FORMDCCONFIG_H
