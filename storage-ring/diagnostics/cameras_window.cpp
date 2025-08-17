#include "cameras_window.h"
#include "ui_cameras_window.h"

CamerasWindow::CamerasWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CamerasWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->btnClose, SIGNAL(clicked()), this, SLOT(close()));

    QFile file(":/configurations/di-cams.json");
    if(!file.open(QIODevice::Text | QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Error", "Could not open DI cams configuration file.", QMessageBox::Ok);
        return;
    }

    QString line;
    QStringList items;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());
    QJsonObject object = jsonDoc.object();
    QJsonArray array = object["cams"].toArray();

    for (QJsonValue value : array) {
        QJsonObject _object = value.toObject();
        std::cout << _object["prefix_p"].toString().toStdString() << " - " << _object["docker"].toString().toStdString() << std::endl;
        CameraWidget* cam = new CameraWidget(_object["prefix_p"].toString(),
                                             _object["prefix_r"].toString(),
                                             _object["model"].toString(),
                                             _object["profile"].toString(),
                                             _object["docker"].toString(), this);
        ui->layout->addWidget( cam );
    }

//    QTextStream configFile(&file);
//    while(!configFile.atEnd()) {
//        line = configFile.readLine();
//        items = line.split(' ');

//        CameraWidget* cam = new CameraWidget(items[0], items[1], items[2], items.size() == 4 ? items[3] : "", this);
//        ui->layout->addWidget( cam );
//    }
}

CamerasWindow::~CamerasWindow()
{
    delete ui;
}
