#include "FormPassword.h"
#include "ui_FormPassword.h"
#include <QCryptographicHash>
#include "qdebug.h"

// initialize static member
bool FormPassword::dialogOpen = false;

FormPassword::FormPassword(QString goldenHash, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormPassword)
{
    ui->setupUi(this);

    this->ui->btnOk->setEnabled(false);
    this->goldenHash = goldenHash;
}

FormPassword::~FormPassword()
{
    delete ui;
}

void FormPassword::on_inputPasswordField_textChanged(const QString &input)
{
    QByteArray inputByteArray = input.toUtf8();
    QString inputHash = QString(QCryptographicHash::hash((inputByteArray), QCryptographicHash::Sha256).toHex());

    if (inputHash == this->goldenHash) {
        this->ui->btnOk->setEnabled((true));
    } else {
        this->ui->btnOk->setEnabled((false));
    }
}

void FormPassword::on_btnOk_clicked()
{
    emit authenticated();
    FormPassword::dialogOpen = false;
    this->close();
}

void FormPassword::on_btnClose_clicked()
{
    FormPassword::dialogOpen = false;
    this->close();
}

void FormPassword::closeEvent(QCloseEvent *event) {
    // This function is useful to handle closing the window from the tab bar (x button)
    FormPassword::dialogOpen = false;
    QWidget::closeEvent(event);
}
