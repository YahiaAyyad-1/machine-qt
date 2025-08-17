#ifndef FORMPARAMETERS_H
#define FORMPARAMETERS_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>

#include <QELabel.h>
#include <qepicspv.h>

#include "client.h"

#define FIRMWARE_SIZE 131072

typedef struct
{
    QString name;
    QString type;
    int index;
} parameter;

typedef union {
    uint32_t i_val;
    float    f_val;
} raw32_t;

namespace Ui {
class FormParameters;
}

class FormParameters : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormParameters(QString group, QWidget *parent = 0);
    ~FormParameters();

private slots:
    void onParametersChanged(QVariant value);

    void on_btnBrowse_clicked();

    void on_btnSave_clicked();

    void on_btnLoad_clicked();

    void on_btnUpload_clicked();

    void on_btnBrowse2_clicked();

    void on_btnUpdateFW_clicked();

private:
    Ui::FormParameters *ui;

    QEpicsPV* pvParameters;
    QString group;
    QList<parameter> parameters;
};

#endif // FORMPARAMETERS_H
