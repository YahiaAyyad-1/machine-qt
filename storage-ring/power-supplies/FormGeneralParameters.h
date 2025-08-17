#ifndef FORMGENERALPARAMETERS_H
#define FORMGENERALPARAMETERS_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>

#include <macros.h>
#include "client.h"

typedef struct
{
    QString name;
    QString type;
    int index;
} parameter_t;

#define FIRMWARE_SIZE   131072
#define FIRMWARE_ARRAY  32768

namespace Ui {
class FormGeneralParameters;
}

class FormGeneralParameters : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormGeneralParameters(QString magnet, QWidget *parent = nullptr);
    ~FormGeneralParameters();

private slots:
    void on_btnBrowse_clicked();

    void on_btnBrowseFW_clicked();

    void on_btnLoad_clicked();

    void on_btnSave_clicked();

    void on_btnUpdateFW_clicked();

    void on_btnResetFW_clicked();

    void on_btnResetParameters_clicked();

    void on_btnUpdateParameters_clicked();

private:
    Ui::FormGeneralParameters *ui;

    QString group;
    QList<parameter_t> parameters;
};

#endif // FORMGENERALPARAMETERS_H
