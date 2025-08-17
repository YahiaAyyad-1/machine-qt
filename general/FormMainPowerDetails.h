#ifndef FORMMAINPOWERDETAILS_H
#define FORMMAINPOWERDETAILS_H

#include <QMainWindow>
#include <widgets/power_meter_widget.h>

namespace Ui {
class FormMainPowerDetails;
}

class FormMainPowerDetails : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormMainPowerDetails(QWidget *parent = nullptr);
    ~FormMainPowerDetails();

private:
    Ui::FormMainPowerDetails *ui;
};

#endif // FORMMAINPOWERDETAILS_H
