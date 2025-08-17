#include "uiMicrotronModulator.h"
#include "ui_uiMicrotronModulator.h"

uiMicrotronModulator::uiMicrotronModulator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::uiMicrotronModulator)
{
    ui->setupUi(this);
}

uiMicrotronModulator::~uiMicrotronModulator()
{
    delete ui;
}
