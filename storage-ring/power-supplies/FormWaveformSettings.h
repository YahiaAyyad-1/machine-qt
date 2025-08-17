#ifndef FORMWAVEFORMSETTINGS_H
#define FORMWAVEFORMSETTINGS_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>

#include <iostream>

#include "macros.h"
#include "client.h"

#ifndef WAVEFORM_SIZE
#define WAVEFORM_SIZE 32768
#endif

namespace Ui {
class FormWaveformSettings;
}

class FormWaveformSettings : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormWaveformSettings(QString magnet, QWidget *parent = 0);
    ~FormWaveformSettings();

private slots:
    void waveformUpload_Clicked();
    void waveformSelect_Clicked();

private:
    Ui::FormWaveformSettings *ui;

    QString group;
};

#endif // FORMWAVEFORMSETTINGS_H
