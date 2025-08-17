#ifndef FORMGENERALWAVEFORM_H
#define FORMGENERALWAVEFORM_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>

#include "macros.h"
#include "client.h"

#ifndef WAVEFORM_SIZE
#define WAVEFORM_SIZE 32768
#endif

namespace Ui {
class FormGeneralWaveform;
}

class FormGeneralWaveform : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormGeneralWaveform(QString magnet, QWidget *parent = nullptr);
    ~FormGeneralWaveform();

    void setCommand(QString command, int id);

private slots:
    void onSizeChanged();

    void onPeriodChanged();

    void onFinalChanged();

    void onTopChanged();

    void onPlotClicked();

    void onBrowseClicked();

    void onUploadClicked();

private:
    Ui::FormGeneralWaveform *ui;

    QString group;
};

#endif // FORMGENERALWAVEFORM_H
