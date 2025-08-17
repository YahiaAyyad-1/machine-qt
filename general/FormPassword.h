#ifndef FORMPASSWORD_H
#define FORMPASSWORD_H

#include <QMainWindow>

namespace Ui {
class FormPassword;
}

class FormPassword : public QMainWindow
{
    Q_OBJECT

public:
    static bool dialogOpen;
    explicit FormPassword(QString goldenHash, QWidget *parent = nullptr);
    ~FormPassword();

signals:
    void authenticated();

private slots:
    void on_inputPasswordField_textChanged(const QString &arg1);

    void on_btnOk_clicked();

    void on_btnClose_clicked();

    void closeEvent(QCloseEvent *event);

private:
    Ui::FormPassword *ui;
    QString goldenHash;
};

#endif // FORMPASSWORD_H
