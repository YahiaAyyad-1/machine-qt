#include "FormScraper.h"
#include "ui_FormScraper.h"

FormScraper::FormScraper(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormScraper)
{
    ui->setupUi(this);
    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));

    this->pvDcct = new QEpicsPV("SRC01-DI-DCCT1:getDcctCurrent");
    this->hlm1 = new QEpicsPV("SR-MO-MC1:SRC01-VSCR-STP-TRSY1.HLM");
    this->hlm2 = new QEpicsPV("SR-MO-MC1:SRC01-VSCR-STP-TRSY2.HLM");
}

FormScraper::~FormScraper()
{
    delete ui;
}

void FormScraper::on_btnScrape_clicked()
{
    if(ui->txtCurrent->text().isEmpty()) {
        QMessageBox::warning(this, "Warning", "Enter Target Current first.");
        return;
    }

    bool ok;
    double current = ui->txtCurrent->text().toDouble(&ok);
    if(!ok) {
        QMessageBox::warning(this, "Warning", "Enter valid value.");
        return;
    }

    if(current >= this->pvDcct->get().toDouble()) {
        QMessageBox::warning(this, "Warning", "Enter value less than the DCCT current");
        return;
    }

    QProcess* command = new QProcess;
    command->start("python3 /home/control/nfs/groups/diagnostics/Scraper_Automation.py " + ui->txtCurrent->text());
    QMessageBox::information(this, "Information", "Target Current Reached");
}

void FormScraper::on_qepushbutton_10_clicked()
{
    Client::writePV("SR-MO-MC1:SRC01-VSCR-STP-TRSY2.VAL", this->hlm2->get().toDouble());
}

void FormScraper::on_qepushbutton_7_clicked()
{
    Client::writePV("SR-MO-MC1:SRC01-VSCR-STP-TRSY1.VAL", this->hlm1->get().toDouble());
}

