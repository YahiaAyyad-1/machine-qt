#ifndef HEAT_ABSORBERS_WINDOW_H
#define HEAT_ABSORBERS_WINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

#include <widgets/heat_absorbers_box_widget.h>

#include "client.h"
#include "macros.h"

namespace Ui {
class HeatAbsorbersWindow;
}

class HeatAbsorbersWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HeatAbsorbersWindow(QWidget *parent = nullptr);
    ~HeatAbsorbersWindow();

private slots:
    void on_btnReset_clicked();

private:
    Ui::HeatAbsorbersWindow *ui;
};

#endif // HEAT_ABSORBERS_WINDOW_H
