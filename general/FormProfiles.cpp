#include "FormProfiles.h"
#include "ui_FormProfiles.h"

FormProfiles::FormProfiles(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormProfiles)
{
    ui->setupUi(this);
    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
}

FormProfiles::~FormProfiles()
{
    delete ui;
}

void FormProfiles::on_btnBrowse_clicked()
{
    if(!QDir(QString(getenv("HOME")) + "/nfs/machine/").exists())
    {
        QMessageBox::critical(this, "Error", "NFS is not mounted.");
        return;
    }

    QString fileName = QFileDialog::getOpenFileName(this, "Select Profile", QString(getenv("HOME")) + "/nfs/machine/profiles", tr("Profiles (*.snp)"));
    if(fileName.isEmpty())
    {
        QMessageBox::critical(this, "Error", "Empty file name.");
        return;
    }

    if(!fileName.endsWith(".snp"))
        fileName += ".snp";
    this->ui->txtFile->setText(fileName);
}

void FormProfiles::on_btnSave_clicked()
{
    QString fileName = this->ui->txtFile->text();
    if(fileName.isEmpty())
    {
        QMessageBox::critical(this, "Error", "Empty file name.");
        return;
    }

    if(!ui->rbFrontEnd->isChecked() && !fileName.startsWith("/home/control/nfs/machine/profiles"))
        fileName = "/home/control/nfs/machine/profiles/" + fileName;
    if(ui->rbFrontEnd->isChecked()  && !fileName.startsWith("/home/control/nfs/machine/frontend_profiles"))
        fileName = "/home/control/nfs/machine/frontend_profiles/" + fileName;

    if(fileName.endsWith(".snp"))
        fileName = fileName.replace(".snp", "");

    QString requestName;
    if(this->ui->rbSR->isChecked()) {
        requestName = QString(getenv("HOME")) + "/nfs/machine/profiles-pv-list/sr-pvs.req";
    }
    else if(this->ui->rbIN->isChecked()) {
        requestName = QString(getenv("HOME")) + "/nfs/machine/profiles-pv-list/injector-pvs.req";
    }
    else if(this->ui->rbAll->isChecked())
    {
        saveProfile(QString(getenv("HOME")) + "/nfs/machine/profiles-pv-list/injector-pvs.req", fileName + "-inj.snp");
        saveProfile(QString(getenv("HOME")) + "/nfs/machine/profiles-pv-list/sr-pvs.req",       fileName + "-sr.snp");

        requestName = QString(getenv("HOME")) + "/nfs/machine/profiles-pv-list/all-pvs.req";
    }
    else if(this->ui->rbFrontEnd->isChecked()) {
        requestName = QString(getenv("HOME")) + "/nfs/machine/profiles-pv-list/bbb-frontend.req";
    }
    else
    {
        QMessageBox::critical(this, "Error", "Choose profile mode.");
        return;
    }

    fileName += ".snp";
    saveProfile(requestName, fileName, true);
}

void FormProfiles::on_btnRestore_clicked()
{
    QString fileName = this->ui->txtFile->text();
    if(fileName.isEmpty())
    {
        QMessageBox::critical(this, "Error", "Empty file name.");
        return;
    }

    loadProfile(fileName);
}

void FormProfiles::saveProfile(QString requestFileName, QString saveFileName, bool showMessage)
{
    int  status = 0;
    char save[100];
    char type[100];
    chid pvID;
    QString line;
    QFile input(requestFileName);
    QFile profile(saveFileName);
    QString missingPVs = "";

    if(!profile.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate))
    {
        QMessageBox::warning(NULL, "Profile Error", "Could not open profile: " + saveFileName);
        return;
    }

    if(!input.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(NULL, "Profile Error", "Could not open request: " + requestFileName);
        return;
    }

    ui->lblInfo->setText("Saving profile ...");
    ui->lblInfo->repaint();
    ui->btnSave->setEnabled(false);
    ui->btnRestore->setEnabled(false);
    ui->btnTime->setEnabled(false);
    ui->btnBrowse->setEnabled(false);
    ui->txtFile->setEnabled(false);

#ifdef BURT_COMPATIBLE
    profile.write("SDDS1\n");
    // profile.write("&parameter name=TimeStamp, type=string, fixed_value=\"Sun Dec 29 09:39:39 2019");
    profile.write(QString("&parameter name=TimeStamp, type=string, fixed_value=\"" + QDateTime::currentDateTime().toString("ddd MMM dd hh:mm:ss yyyy\n")).toStdString().c_str());
    profile.write("\", &end\n");
    profile.write("&parameter name=LoginID, type=string, fixed_value=\"control (Control-Group)\", &end\n");
    profile.write("&parameter name=EffectiveUID, type=string, fixed_value=4400, &end\n");
    profile.write("&parameter name=GroupID, type=string, fixed_value=4400, &end\n");
    profile.write("&parameter name=BurtKeywords, type=string, fixed_value=\"\", &end\n");
    profile.write("&parameter name=BurtComments, type=string, fixed_value=\"\", &end\n");
    profile.write("&parameter name=SnapType, type=string, fixed_value=Absolute, &end\n");
    profile.write("&column name=ControlName, type=string,  &end\n");
    profile.write("&column name=ControlType, type=string,  &end\n");
    profile.write("&column name=Lineage, type=string,  &end\n");
    profile.write("&column name=BackupMsg, type=string,  &end\n");
    profile.write("&column name=RestoreMsg, type=string,  &end\n");
    profile.write("&column name=ControlMode, type=string,  &end\n");
    profile.write("&column name=Count, type=long,  &end\n");
    profile.write("&column name=ValueString, type=string,  &end\n");
    profile.write("&data mode=ascii, &end\n");
    profile.write("! page number 1\n");

    if(this->ui->rbSR->isChecked())
        profile.write("                 157\n");
    else if(this->ui->rbIN->isChecked())
        profile.write("                 164\n");
    else/* if(this->ui->rbAll->isChecked())*/
        profile.write("                 321\n");
#endif

    while(!input.atEnd())
    {
        line = input.readLine();
        line.remove(line.length() - 1, 1);

        epicsDoublePV double_pv;
        epicsEnumPV enum_pv;
        epicsLongPV long_pv;
        epicsStringPV string_pv;
        epicsCharacterPV char_pv;

        ca_search(line.toStdString().c_str(), &pvID);
        status = ca_pend_io(1);
        if(status != ECA_NORMAL)
        {
            missingPVs += line + "\n";
            continue;
        }

        sprintf(type, "%s", dbr_type_to_text(ca_field_type(pvID)));
        if(strncmp(type, "DBR_DOUBLE", sizeof(type)) == 0)
        {
            double_pv.channel = pvID;
            cainfo(double_pv, DBF_DOUBLE);
            caget(double_pv, DBF_DOUBLE);

            status = ca_pend_io(1);
            if(status != ECA_NORMAL)
            {
                missingPVs += line + "\n";
                continue;
            }

            memset(save, '\0', sizeof(save));
#ifdef BURT_COMPATIBLE
            sprintf(save, "%s pv - - - - 1 %.15e\n", ca_name(double_pv.channel), double_pv.data.value);
#else
            sprintf(save, "%s %.10e\n", ca_name(double_pv.channel), double_pv.data.value);
#endif
            profile.write(save);
        }
        else if(strncmp(type, "DBR_LONG", sizeof(type)) == 0)
        {
            long_pv.channel = pvID;
            cainfo(long_pv, DBF_LONG);
            caget(long_pv, DBF_LONG);

            status = ca_pend_io(1);
            if(status != ECA_NORMAL)
            {
                missingPVs += line + "\n";
                continue;
            }

            memset(save, '\0', sizeof(save));
#ifdef BURT_COMPATIBLE
            sprintf(save, "%s pv - - - - 1 %i\n", ca_name(long_pv.channel), long_pv.data.value);
#else
            sprintf(save, "%s %i\n", ca_name(long_pv.channel), long_pv.data.value);
#endif
            profile.write(save);
        }
        else if(strncmp(type, "DBR_ENUM", sizeof(type)) == 0)
        {
            enum_pv.channel = pvID;
            cainfo(enum_pv, DBF_ENUM);
            caget(enum_pv, DBF_ENUM);

            status = ca_pend_io(1);
            if(status != ECA_NORMAL)
            {
                missingPVs += line + "\n";
                continue;
            }

            memset(save, '\0', sizeof(save));
#ifdef BURT_COMPATIBLE
            sprintf(save, "%s pv - - - - 1 %s\n", ca_name(enum_pv.channel), (enum_pv.data.value < enum_pv.info.no_str) ? enum_pv.info.strs[enum_pv.data.value] : "");
#else
            sprintf(save, "%s %s\n", ca_name(enum_pv.channel), (enum_pv.data.value < enum_pv.info.no_str) ? enum_pv.info.strs[enum_pv.data.value] : "");
#endif
            profile.write(save);
        }
        else if(strncmp(type, "DBR_STRING", sizeof(type)) == 0)
        {
            string_pv.channel = pvID;
            caget(string_pv, DBF_STRING);

            status = ca_pend_io(1);
            if(status != ECA_NORMAL)
            {
                missingPVs += line + "\n";
                continue;
            }

            memset(save, '\0', sizeof(save));
#ifdef BURT_COMPATIBLE
            sprintf(save, "%s pv - - - - 1 %s\n", ca_name(string_pv.channel), string_pv.data.value);
#else
            sprintf(save, "%s %s\n", ca_name(string_pv.channel), string_pv.data.value);
#endif
            profile.write(save);
        }
        else if(strncmp(type, "DBR_CHAR", sizeof(type)) == 0)
        {
            char_pv.channel = pvID;
            cainfo(char_pv, DBF_CHAR);
            caget(char_pv, DBF_CHAR);

            status = ca_pend_io(1);
            if(status != ECA_NORMAL)
            {
                missingPVs += line + "\n";
                continue;
            }

            memset(save, '\0', sizeof(save));
#ifdef BURT_COMPATIBLE
            if(/*char_pv.data.value >= 0 && */char_pv.data.value <= 31)
                sprintf(save, "%s pv - - - - 1 %c\n", ca_name(char_pv.channel), char_pv.data.value + 48);
            else
                sprintf(save, "%s pv - - - - 1 %c\n", ca_name(char_pv.channel), char_pv.data.value);
#else
            if(/*char_pv.data.value >= 0 && */char_pv.data.value <= 31)
                sprintf(save, "%s %c\n", ca_name(char_pv.channel), char_pv.data.value + 48);
            else
                sprintf(save, "%s %c\n", ca_name(char_pv.channel), char_pv.data.value);
#endif
            profile.write(save);
        }
        else
        {
            missingPVs += line + "\n";
            continue;
        }

        QApplication::processEvents();
    }

    ui->btnSave->setEnabled(true);
    ui->btnRestore->setEnabled(true);
    ui->btnTime->setEnabled(true);
    ui->btnBrowse->setEnabled(true);
    ui->txtFile->setEnabled(true);
    ui->lblInfo->setText("Done");
    ui->lblInfo->repaint();
    if (showMessage)
    {
        if(missingPVs.isEmpty())
        {
            QMessageBox::information(0, "Profile Save", "Profile " + saveFileName + " saved successfully.");
        }
        else
        {
            QMessageBox::warning(0, "Profile Save", "Profile " + saveFileName + " is saved but incomplete. The following PVs are missing:\n" + missingPVs);
        }
    }

    profile.close();
    input.close();
    return;
}

void FormProfiles::loadProfile(QString saveFileName)
{
    int  count = 0;
    int  status = 0;
    short fieldType;
    chid pvID;
    QString line;
    QStringList data;
    QString missingPVs = "";
    QFile profile(saveFileName);

    if(!profile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(NULL, "Profile Error", "Unable to open profile: " + saveFileName);
        return;
    }

    ui->lblInfo->setText("Loading profile ...");
    ui->lblInfo->repaint();
    ui->btnSave->setEnabled(false);
    ui->btnRestore->setEnabled(false);
    while(!profile.atEnd())
    {
        line = profile.readLine();
        line.remove(line.length() - 1, 1);
        if(line.isEmpty() || line[0] == '\n' || line[0] == '&' || line[0] == '!' || isspace(line[0].toLatin1()) || line[0] == '"' || line == "SDDS1")
            continue;

        line = line.trimmed();
        data.clear();
        data.push_back(line.section(' ', 0, 0));
        if(line.contains(" - - - - "))
            data.push_back(line.section(' ', 7, -1));
        else
            data.push_back(line.section(' ', 1, -1));

        epicsEnumPV enum_pv;
        ca_search(data[0].toStdString().c_str(), &pvID);
        status = ca_pend_io(1);
        if(status != ECA_NORMAL)
        {
            missingPVs += data[0] + "\n";
            continue;
        }

        fieldType = ca_field_type(pvID);
        if(fieldType == DBR_DOUBLE)
        {
            double v = data[1].toDouble();
            ca_put(DBF_DOUBLE, pvID, &v);
            count++;
        }
        else if(fieldType == DBR_LONG)
        {
            long v = data[1].toLong();
            ca_put(DBR_LONG, pvID, &v);
            count++;
        }
        else if(fieldType == DBR_ENUM)
        {
            enum_pv.channel = pvID;
            cainfo(enum_pv, DBF_ENUM);
            caget(enum_pv, DBF_ENUM);
            status = ca_pend_io(1);

            unsigned short i = 0;
            unsigned short v = UCHAR_MAX;
            for(i = 0; i < enum_pv.info.no_str; i++)
            {
                if(strncmp(enum_pv.info.strs[i], data[1].toStdString().c_str(), strlen(data[1].toStdString().c_str())) == 0)
                {
                    v = i;
                    break;
                }
            }
            ca_put(DBR_ENUM, pvID, &v);
            count++;
        }
        else if(fieldType == DBR_STRING)
        {
            ca_put(DBR_STRING, pvID, data[1].toStdString().c_str());
            count++;
        }
        else if(fieldType == DBR_CHAR)
        {
            char c = data[1][0].toLatin1() - 48;
            ca_put(DBR_CHAR, pvID, &c);
            count++;
        }
        else
        {
            missingPVs += data[0] + "\n";
            continue;
        }

        if(ui->rbFrontEnd->isChecked()) {
            QThread::sleep(1);
            QCoreApplication::processEvents();
        }
    }

    ui->btnSave->setEnabled(true);
    ui->btnRestore->setEnabled(true);
    ui->lblInfo->setText("Done.");
    ui->lblInfo->repaint();
    status = ca_pend_io(count);
    if(status != ECA_NORMAL || !missingPVs.isEmpty())
        QMessageBox::warning(0, "Profile Load", "Profile " + saveFileName + " is loaded but incomplete. The following PVs are missing:\n" + missingPVs);
    else
        QMessageBox::information(0, "Profile Load", "Profile " + saveFileName + " loaded successfully.");

    profile.close();
    return;
}

void FormProfiles::on_btnTime_clicked()
{
//    ui->txtFile->setText(QString(getenv("HOME")) +
//                         "/nfs/machine/" +
//                         (ui->rbFrontEnd->isChecked() ? "frontend_profiles/" : "profiles/") +
//                         QDateTime::currentDateTime().toString("yyyyMMdd-hhmm") + ".snp");
    ui->txtFile->setText(QDateTime::currentDateTime().toString("yyyyMMdd-hhmm"));
}
