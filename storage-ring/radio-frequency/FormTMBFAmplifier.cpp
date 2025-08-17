#include "FormTMBFAmplifier.h"
#include "ui_FormTMBFAmplifier.h"

FormTMBFAmplifier::FormTMBFAmplifier(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormTMBFAmplifier)
{
    ui->setupUi(this);

    CONNECT_CLOSE_BUTTON;
}

FormTMBFAmplifier::~FormTMBFAmplifier()
{
    delete ui;
}
