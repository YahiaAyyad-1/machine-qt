#include "sr_ps_window.h"
#include "ui_sr_ps_window.h"

RingPowerSupplyWindow::RingPowerSupplyWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RingPowerSupplyWindow)
{
    ui->setupUi(this);
    CONNECT_CLOSE_BUTTON;

    ui->ltDipole->insertWidget(ui->ltDipole->count(), new PowerSupplyWidget("SR-PS-BM", this));
    ui->ltSFocus->insertWidget(ui->ltSFocus->count(), new PowerSupplyWidget("SR-PS-SF1", this));
    ui->ltSFocus->insertWidget(ui->ltSFocus->count(), new PowerSupplyWidget("SR-PS-SF2", this));
    ui->ltSDefocus->insertWidget(ui->ltSDefocus->count(), new PowerSupplyWidget("SR-PS-SD1", this));
    ui->ltSDefocus->insertWidget(ui->ltSDefocus->count(), new PowerSupplyWidget("SR-PS-SD2", this));
    for(int i = 1; i <= 16; i++) {
        ui->ltFocus->insertWidget(ui->ltFocus->count(), new PowerSupplyWidget(QString::asprintf("SRC%02d-PS-QF1", i), this));
        ui->ltFocus->insertWidget(ui->ltFocus->count(), new PowerSupplyWidget(QString::asprintf("SRC%02d-PS-QF2", i), this));
        ui->ltDefocus->insertWidget(ui->ltDefocus->count(), new PowerSupplyWidget(QString::asprintf("SRC%02d-PS-QD1", i), this));
        ui->ltDefocus->insertWidget(ui->ltDefocus->count(), new PowerSupplyWidget(QString::asprintf("SRC%02d-PS-QD2", i), this));
    }

    this->rampingWithRF = true;

    this->machineMode = new QEpicsPV("Machine:Status");
    QObject::connect(this->machineMode, SIGNAL(valueChanged(QVariant)), this, SLOT(onMachineStateChanged(QVariant)));

    this->qfCurrent = new QEpicsPV("SR-PS-SEQ:setQFCurrent");
    this->qdCurrent = new QEpicsPV("SR-PS-SEQ:setQDCurrent");
    this->sfCurrent = new QEpicsPV("SR-PS-SEQ:setSFCurrent");
    this->sdCurrent = new QEpicsPV("SR-PS-SEQ:setSDCurrent");
    QObject::connect(this->qfCurrent, SIGNAL(connected()), this, SLOT(onQFConnected()));
    QObject::connect(this->qdCurrent, SIGNAL(connected()), this, SLOT(onQDConnected()));
    QObject::connect(this->sfCurrent, SIGNAL(connected()), this, SLOT(onSFConnected()));
    QObject::connect(this->sdCurrent, SIGNAL(connected()), this, SLOT(onSDConnected()));

    this->timer = new QTimer(this);
    this->timer->setInterval(1000);
    QObject::connect(this->timer, SIGNAL(timeout()), this, SLOT(onAllStateChanged()));
    this->timer->start();

    this->pulsed = NULL;
    this->correctors = NULL;
    this->health = NULL;

    checkContentSize();
}

RingPowerSupplyWindow::~RingPowerSupplyWindow()
{
    delete ui;
}

void RingPowerSupplyWindow::onAllStateChanged()
{
    int open = 0;
    int off = 0;
    int stand = 0;
    int on = 0;
    int dc = 0;
    int wave = 0;
    QList<int> states;
    QList<int> modes;

    for(PowerSupplyWidget* w : this->findChildren<PowerSupplyWidget*>()) {
        states.push_back(w->psState);
        modes.push_back(w->psMode);
    }

    for(int value : states) {
        if(value == 4)
            open++;
        else if(value == 1)
            stand++;
        else if(value == 0)
            off++;
        else if(value == 2)
            on++;
    }

    for(int value : modes) {
        if(value == 0)
            dc++;
        else if(value == 1)
            wave++;
        else
            continue;
    }

    if(open == MAGNETS_COUNT)
        ui->ledOpen->setValue(2);
    else if(open > 0 && open < MAGNETS_COUNT)
        ui->ledOpen->setValue(1);
    else
        ui->ledOpen->setValue(0);

    if(stand == MAGNETS_COUNT)
        ui->ledStandby->setValue(2);
    else if(stand > 0 && stand < MAGNETS_COUNT)
        ui->ledStandby->setValue(1);
    else
        ui->ledStandby->setValue(0);

    if(off == MAGNETS_COUNT)
        ui->ledOFF->setValue(2);
    else if(off > 0 && off < MAGNETS_COUNT)
        ui->ledOFF->setValue(1);
    else
        ui->ledOFF->setValue(0);

    if(on == MAGNETS_COUNT)
        ui->ledON->setValue(2);
    else if(on > 0 && on < MAGNETS_COUNT)
        ui->ledON->setValue(1);
    else
        ui->ledON->setValue(0);

    if(dc == MAGNETS_COUNT)
        ui->ledDC->setValue(2);
    else if(dc > 0 && dc < MAGNETS_COUNT)
        ui->ledDC->setValue(1);
    else
        ui->ledDC->setValue(0);

    if(wave == MAGNETS_COUNT)
        ui->ledWaveform->setValue(2);
    else if(wave > 0 && wave < MAGNETS_COUNT)
        ui->ledWaveform->setValue(1);
    else
        ui->ledWaveform->setValue(0);
}

void RingPowerSupplyWindow::on_btnReset_clicked()
{
    for(PowerSupplyWidget* w : this->findChildren<PowerSupplyWidget*>()) {
        Client::writePV(w->prefix + ":setCommand", 4);
    }
}

void RingPowerSupplyWindow::on_btnPulsed_clicked()
{
    OPEN_UI(this->pulsed, FormPulsedElements, this);
}

void RingPowerSupplyWindow::on_btnCorrectors_clicked()
{
    OPEN_UI(this->correctors, RingCorrectorsWindow, this);
}

void RingPowerSupplyWindow::on_btnCycle_clicked()
{
    QProcess* p = new QProcess;
    p->setWorkingDirectory(getenv("HOME"));
    p->start("gnome-terminal --geometry 100x30 -x python3 bin/Cycle_Magnets.py");
}

void RingPowerSupplyWindow::on_btnRamp_clicked()
{
    QProcess* p = new QProcess;
    p->setWorkingDirectory(getenv("HOME"));
    p->start("gnome-terminal --geometry 100x30 -x python3 bin/PS_Ramping.py");

    if (this->rampingWithRF)
    {
        QProcess* p2 = new QProcess;
        p2->setWorkingDirectory("/home/control/nfs/groups/accelerator-physics/matlab_screepts");
        p2->start("gnome-terminal --geometry 100x30 -x /home/control/nfs/groups/accelerator-physics/matlab_screepts/rf_ramp_test.sh");
    }
}

void RingPowerSupplyWindow::on_btnHealth_clicked()
{
    OPEN_UI(this->health, FormGatewaysHealth, this);
}


void RingPowerSupplyWindow::on_cbGeneralControl_currentIndexChanged(int index)
{
    switch(index)
    {
    case 1:
        this->general = new FormGeneralControl("QF");
        this->general->show();
        break;

    case 2:
        this->general = new FormGeneralControl("QD");
        this->general->show();
        break;

    case 3:
        this->general = new FormGeneralControl("SF");
        this->general->show();
        break;

    case 4:
        this->general = new FormGeneralControl("SD");
        this->general->show();
        break;

    default:
        break;
    }

    this->ui->cbGeneralControl->setCurrentIndex(0);
}

void RingPowerSupplyWindow::onMachineStateChanged(QVariant value)
{
    bool condition = value.toInt() != 3 && value.toInt() != 6 && value.toInt() != 7;
    ui->btnSetQF->setEnabled(condition); //btnStandby btnOpenloop btnOFF
    ui->btnSetQD->setEnabled(condition);
    ui->btnSetSF->setEnabled(condition);
    ui->btnSetSD->setEnabled(condition);
    ui->txtQDCurrent->setEnabled(condition);
    ui->txtQFCurrent->setEnabled(condition);
    ui->txtSDCurrent->setEnabled(condition);
    ui->txtSFCurrent->setEnabled(condition);
    ui->btnCycle->setEnabled(condition);
    ui->btnRamp->setEnabled(condition);

     ui->btnStandby->setEnabled(condition);
     ui->btnOpenloop->setEnabled(condition);
     ui->btnOFF->setEnabled(condition);
}

void RingPowerSupplyWindow::onQFConnected()
{
    ui->txtQFCurrent->setText(ui->lblQF->text());
}

void RingPowerSupplyWindow::onQDConnected()
{
    ui->txtQDCurrent->setText(ui->lblQD->text());
}

void RingPowerSupplyWindow::onSFConnected()
{
    ui->txtSFCurrent->setText(ui->lblSF->text());
}

void RingPowerSupplyWindow::onSDConnected()
{
    ui->txtSDCurrent->setText(ui->lblSD->text());
}

void RingPowerSupplyWindow::on_btnSetQF_clicked()
{
    setPSCurrent(ui->txtQFCurrent, ui->lblQF, "QF");
}

void RingPowerSupplyWindow::on_btnSetQD_clicked()
{
    setPSCurrent(ui->txtQDCurrent, ui->lblQD, "QD");
}

void RingPowerSupplyWindow::on_btnSetSF_clicked()
{
    setPSCurrent(ui->txtSFCurrent, ui->lblSF, "SF");
}

void RingPowerSupplyWindow::on_btnSetSD_clicked()
{
    setPSCurrent(ui->txtSDCurrent, ui->lblSD, "SD");
}

void RingPowerSupplyWindow::setPSCurrent(QLineEdit *txt, QELabel *lbl, QString currentSet)
{
    int status;
    float readPrevious;
    double value;
    QString pvName;
    QString msg;
    QMessageBox::StandardButton reply;

    status = this->machineMode->get().toInt();
    value = txt->text().toFloat();
    readPrevious = lbl->text().toFloat();
    pvName = lbl->getVariableNameProperty();

    if(qAbs(value - readPrevious) > 0.1 && (status == 7 or status == 3))
    {
        QMessageBox::warning(this, "Error", "You have passed the set current difference threshold, Power supplies current won't be changed");
        return;
    }

    msg = QString("You are setting the %1 current to %2 while the currently set value is %3. Do you want to proceed ")
                     .arg(currentSet, QString::number(value), QString::number(readPrevious));
    reply = QMessageBox::question(this, "Save", msg, QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        Client::writePV(pvName, value);
    }
}

void RingPowerSupplyWindow::on_btnWaveform_clicked()
{
    for(PowerSupplyWidget* w : this->findChildren<PowerSupplyWidget*>()) {
        Client::writePV(w->prefix + ":setMode", "Waveform");
    }
}

void RingPowerSupplyWindow::on_btnDC_clicked()
{
    for(PowerSupplyWidget* w : this->findChildren<PowerSupplyWidget*>()) {
        Client::writePV(w->prefix + ":setMode", "DC");
    }
}

void RingPowerSupplyWindow::on_btnStandby_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation", "Are you sure you want to change the PS mode to Standby?",
                                          QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        for(PowerSupplyWidget* w : this->findChildren<PowerSupplyWidget*>()) {
            Client::writePV(w->prefix + ":setCommand", 1);
        }
    }
}

void RingPowerSupplyWindow::on_btnON_clicked()
{
    for(PowerSupplyWidget* w : this->findChildren<PowerSupplyWidget*>()) {
        Client::writePV(w->prefix + ":setCommand", 2);
    }
}

void RingPowerSupplyWindow::on_btnOpenloop_clicked()
{
    for(PowerSupplyWidget* w : this->findChildren<PowerSupplyWidget*>()) {
        Client::writePV(w->prefix + ":setCommand", 5);
    }
}

void RingPowerSupplyWindow::on_btnOFF_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation", "Are you sure you want to change the PS mode to OFF?",
                                          QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        for(PowerSupplyWidget* w : this->findChildren<PowerSupplyWidget*>()) {
            Client::writePV(w->prefix + ":setCommand", 0);
        }
    }
}

void RingPowerSupplyWindow::on_chkBoxIncludeRF_clicked(bool checked)
{
    this->rampingWithRF = checked;
}

void RingPowerSupplyWindow::checkContentSize()
{
    // Get the size of the content
    QSize contentSize = ui->scrollAreaWidgetContents->sizeHint();

    // Get the size of the viewport
    QSize viewportSize = ui->scrollArea->viewport()->size();

    // Compare the sizes
    if (contentSize.height() <= viewportSize.height() && contentSize.width() <= viewportSize.width()) {
        ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    } else {
        ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    }
}
