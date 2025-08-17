#include "FormIOCStats.h"
#include "ui_FormIOCStats.h"

FormIOCStats::FormIOCStats(QString group, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormIOCStats)
{
    ui->setupUi(this);
    this->group = group;
    this->ui->lblTitle->setText(this->group + " Manager");
    QObject::connect(this->ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
    // SET_QELABEL_GROUP;
    // SET_QEPUSHBUTTON_GROUP;
    SET_GROUP(QELabel);
    SET_GROUP(QEPushButton);

    this->ui->cbMode->setVariableNameSubstitutionsProperty("group=" + this->group);
}

FormIOCStats::~FormIOCStats()
{
    delete ui;
}

void FormIOCStats::on_pushButton_clicked()
{
    this->limits = new FormIOCLimits(this->group);
    this->limits->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, this->limits->size(), qApp->desktop()->availableGeometry()));
    this->limits->show();
}
