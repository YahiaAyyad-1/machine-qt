#ifndef FORMBOOSTERDI_H
#define FORMBOOSTERDI_H

#include <QMainWindow>

#include "FormBoosterSRM.h"
#include "FormShaker.h"
#include "FormAFG.h"
#include "FormLiberaMain.h"
#include "storage-ring/diagnostics/FormDCCTExpert.h"
#include "storage-ring/diagnostics/scopes_window.h"

#include "macros.h"

namespace Ui {
class FormBoosterDI;
}

class FormBoosterDI : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormBoosterDI(QWidget *parent = 0);
    ~FormBoosterDI();

private slots:
    void on_btnMoveScreens_clicked();

    void on_btnOpenSRM_clicked();

    void on_btnOpenDCCT_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_14_clicked();

    void on_btnScopes_clicked();

private:
    Ui::FormBoosterDI *ui;

    FormBoosterSRM* srm;
    FormDCCTExpert* dcct;
    FormShaker* shaker;
    FormAFG* afg;
    FormLiberaMain* libera;
    ScopesWindow* scopes;
};

#endif // FORMBOOSTERDI_H
