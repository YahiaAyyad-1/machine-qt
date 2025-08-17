#ifndef PINHOLE_WINDOW_H
#define PINHOLE_WINDOW_H

#include <QMainWindow>
#include "macros.h"

namespace Ui {
class PinholeWindow;
}

class PinholeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PinholeWindow(QWidget *parent = nullptr);
    ~PinholeWindow();

private slots:
    void on_btnGUI_clicked();

    void on_btnImageJ_clicked();

private:
    Ui::PinholeWindow *ui;
};

#endif // PINHOLE_WINDOW_H
