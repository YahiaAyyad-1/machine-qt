#include "microtron_coils_window.h"
#include "ui_microtron_coils_window.h"

MicrotronCoilsWindow::MicrotronCoilsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MicrotronCoilsWindow)
{
    ui->setupUi(this);

    for(int i = 1; i <= 4; i++) {
        CaenPowerSupplyWidget* ps = new CaenPowerSupplyWidget("MI-PS-TC" + STRING(i), false, this);
        ui->ltCoils->addWidget(ps);
    }

    CONNECT_CLOSE_BUTTON;
}

MicrotronCoilsWindow::~MicrotronCoilsWindow()
{
    delete ui;
}
