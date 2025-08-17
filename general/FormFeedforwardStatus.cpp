#include "FormFeedforwardStatus.h"
#include "ui_FormFeedforwardStatus.h"

FormFeedforwardStatus::FormFeedforwardStatus(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormFeedforwardStatus)
{
    ui->setupUi(this);
    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
}

FormFeedforwardStatus::~FormFeedforwardStatus()
{
    delete ui;
}
