#ifndef CAMERA_WIDGET_H
#define CAMERA_WIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QTextStream>

#include <iostream>

namespace Ui {
class CameraWidget;
}

class CameraWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CameraWidget(QString prefix, QString cam, QString model, QString profile, QString docker, QWidget *parent = nullptr);
    ~CameraWidget();

private slots:
    void on_btnRestart_clicked();

    void on_btnStopIOC_clicked();

private:
    Ui::CameraWidget *ui;
    QString dockerImage;
};

#endif // CAMERA_WIDGET_H
