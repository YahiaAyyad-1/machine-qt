#ifndef FORMSCRAPER_H
#define FORMSCRAPER_H

#include <QMainWindow>
#include <QMessageBox>

#include "qepicspv.h"
#include "client.h"

namespace Ui {
class FormScraper;
}

class FormScraper : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormScraper(QWidget *parent = 0);
    ~FormScraper();

private slots:
    void on_btnScrape_clicked();

    void on_qepushbutton_10_clicked();

    void on_qepushbutton_7_clicked();

private:
    Ui::FormScraper *ui;

    QEpicsPV* pvDcct;
    QEpicsPV* hlm1;
    QEpicsPV* hlm2;
};

#endif // FORMSCRAPER_H
