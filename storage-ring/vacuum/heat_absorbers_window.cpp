#include "heat_absorbers_window.h"
#include "ui_heat_absorbers_window.h"

HeatAbsorbersWindow::HeatAbsorbersWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HeatAbsorbersWindow)
{
    ui->setupUi(this);
    CONNECT_CLOSE_BUTTON;

    QFile file(":/configurations/sr-heat-absorbers.txt", this);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(this, "Error", "Could not open config file.", QMessageBox::Ok);
        return;
    }

    QTextStream configFile(&file);
    int count = 0;
    int row;
    int column;
    QString line;
    while(!configFile.atEnd()) {
        line   = configFile.readLine();
        row    = count / 4;
        column = count % 4;
        ui->grid->addWidget(new HeatAbsorbersBoxWidget(line, this), row, column);
        count++;
    }

//    QPushButton* button = new QPushButton("Reset", this);
//    QObject::connect(button, &QPushButton::clicked, this, [](){
//        Client::writePV("SR-VA-HAB:reset", 1);
//        Client::writePV("SRC3-CO-HAB:resetInterlock", 1);
//        Client::writePV("BEATS-WIGGLER:reset", 1);
//    });

//    ui->grid->addWidget(button, count / 4, count % 4);
}

HeatAbsorbersWindow::~HeatAbsorbersWindow()
{
    delete ui;
}

void HeatAbsorbersWindow::on_btnReset_clicked()
{
    Client::writePV("SR-VA-HAB:reset", 1);
    Client::writePV("SRC3-CO-HAB:resetInterlock", 1);
    Client::writePV("BEATS-WIGGLER:reset", 1);
}
