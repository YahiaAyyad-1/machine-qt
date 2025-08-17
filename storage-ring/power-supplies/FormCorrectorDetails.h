#ifndef FORMCORRECTORDETAILS_H
#define FORMCORRECTORDETAILS_H

#include <QMainWindow>
#include <QHash>
#include <QDesktopWidget>
#include <QMessageBox>

#include <qepicspv.h>

#include "FormCorrectorPlotter.h"
#include "FormCorrectorTuning.h"
#include "FormCorrectorsReadings.h"

namespace Ui {
class FormCorrectorDetails;
}

class FormCorrectorDetails : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormCorrectorDetails(QString group, QWidget *parent = 0);
    ~FormCorrectorDetails();

private slots:
    void faultsChanged(QVariant value);

    void stateHandlerChanged();

    void on_btnPlotter_clicked();

    void on_btnTuning_clicked();

    void on_btnReadings_clicked();

private:
    Ui::FormCorrectorDetails *ui;

    FormCorrectorPlotter* plotter;
    FormCorrectorTuning*  tuning;
    FormCorrectorsReadings* readings;

    QString group;
    QHash<int, QString> messages;

    QEpicsPV* faults;
    QEpicsPV* state;
};

#endif // FORMCORRECTORDETAILS_H
