#ifndef CAMERAS_WINDOW_H
#define CAMERAS_WINDOW_H

#include <QMainWindow>
#include "macros.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <widgets/camera_widget.h>

#include <iostream>

namespace Ui {
class CamerasWindow;
}

class CamerasWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CamerasWindow(QWidget *parent = nullptr);
    ~CamerasWindow();

private:
    Ui::CamerasWindow *ui;
};

#endif // CAMERAS_WINDOW_H
