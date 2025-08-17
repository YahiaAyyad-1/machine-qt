#ifndef FORMMPS_H
#define FORMMPS_H

#include <QMainWindow>

#include "qepicspv.h"
#include "client.h"

#include "general/FormBeamlinesInterlocks.h"

namespace Ui {
class FormMPS;
}

class FormMPS : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormMPS(QWidget *parent = 0);
    ~FormMPS();

private slots:
    void on_btnIRreset_clicked();

    void on_btnReset_clicked();

    void on_btnXAFSreset_clicked();

    void on_btnMSreset_clicked();

    void on_btnBEATSreset_clicked();

    void on_btnHESEBreset_clicked();

    void on_btnOpenXAFS_clicked();

    void on_btnResetSRM_clicked();

    void onShutterStateChanged();

    void on_btnBeamlinesInterlocks_clicked();

    void on_btnResetSXT_clicked();

    void on_btnResetQD_clicked();

    void onSextupolesMontitorPVChanged(const QVariant&);

    void onSextupolesIsLatchedInterlockChanged(const QVariant&);

    void onQuadrupolesMontitorPVChanged(const QVariant&);

    void onQuadrupolesIsLatchedInterlockChanged(const QVariant&);

private:
    Ui::FormMPS *ui;

    const QString greenColor;
    const QString yellowColor;
    const QString redColor;

    QEpicsPV* pvIRValve;
    QEpicsPV* pvXafsValve;
    QEpicsPV* pvShutterFault;
    QEpicsPV* pvShutterClosed;
    QEpicsPV* pvShutterOpened;
    QEpicsPV* pvSextupolesMontitor;
    QEpicsPV* pvSextupolesIsLatchedInterlock;
    QEpicsPV* pvQuadrupolesMontitor;
    QEpicsPV* pvQuadrupolesIsLatchedInterlock;
};

#endif // FORMMPS_H
