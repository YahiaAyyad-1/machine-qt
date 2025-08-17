#ifndef FORMPROFILES_H
#define FORMPROFILES_H

#include <QMainWindow>
#include <QFile>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include <QThread>

#include "client.h"

#include <cadef.h>
#include <db_access.h>

#define BURT_COMPATIBLE

namespace Ui {
class FormProfiles;
}

class FormProfiles : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormProfiles(QWidget *parent = 0);
    ~FormProfiles();
    void saveProfile(QString requestFileName, QString saveFileName, bool showMessage = false);
    void loadProfile(QString saveFileName);

private slots:
    void on_btnBrowse_clicked();

    void on_btnSave_clicked();

    void on_btnRestore_clicked();

    void on_btnTime_clicked();

private:
    Ui::FormProfiles *ui;
};

#endif // FORMPROFILES_H
