#include "FormRFDiagnostics.h"
#include "ui_FormRFDiagnostics.h"

FormRFDiagnostics::FormRFDiagnostics(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormRFDiagnostics)
{
    ui->setupUi(this);
    CONNECT_CLOSE_BUTTON;
}

FormRFDiagnostics::~FormRFDiagnostics()
{
    delete ui;
}

void FormRFDiagnostics::on_btnBrowse_clicked()
{
    QString line;
    QFile file;
    QTextStream log;
    QString fileName;
    int value, index = 0, ssa, dis;
    bool ok;

    if(!QDir(QString(getenv("HOME")) + "/nfs/machine/").exists()) {
        QMessageBox::critical(this, "Error", "NFS is not mounted.");
        return;
    }

    fileName = QFileDialog::getOpenFileName(this, "Select File", QString(getenv("HOME")) + "/nfs/machine", "Text Files (*.txt)");
    if(fileName.isEmpty()) {
        QMessageBox::critical(this, "Error", "No file selected.");
        return;
    }

    ui->txtFileName->setText(fileName);
    file.setFileName(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Could not open log file " + fileName);
        return;
    }

    log.setDevice(&file);
    while(!log.atEnd()) {
        line = log.readLine();
        value = line.toInt(&ok);
        if(!ok) {
            QMessageBox::critical(this, "Error", "Invalid log file");
            file.close();
            return;
        }

        ssa = (index / 11) + 1;
        dis =  index % 11;
        for(int i = 0; i <= 7; i++) {
            this->findChild<QSimpleShape*>(QString::asprintf("ledSSA%d_%d_%d", ssa, dis, i))->setValue( (value >> i) & 0x1 );
        }
        if(dis == 0) {
            this->findChild<QSimpleShape*>(QString::asprintf("ledSSA%d_%d_%d", ssa, dis,  8))->setValue( (value >> 0x9) & 0x1 );
            this->findChild<QSimpleShape*>(QString::asprintf("ledSSA%d_%d_%d", ssa, dis,  9))->setValue( (value >> 0xa) & 0x1 );
            this->findChild<QSimpleShape*>(QString::asprintf("ledSSA%d_%d_%d", ssa, dis, 10))->setValue( (value >> 0xb) & 0x1 );
            this->findChild<QSimpleShape*>(QString::asprintf("ledSSA%d_%d_%d", ssa, dis, 11))->setValue( (value >> 0xc) & 0x1 );
        }
        else {
            this->findChild<QSimpleShape*>(QString::asprintf("ledSSA%d_%d_%d", ssa, dis,  8))->setValue( (value >> 0x8) & 0x1 );
            this->findChild<QSimpleShape*>(QString::asprintf("ledSSA%d_%d_%d", ssa, dis,  9))->setValue( (value >> 0xc) & 0x1 );
        }

        index++;
    }

    file.close();
}

