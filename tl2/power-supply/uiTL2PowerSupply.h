#ifndef UITL2POWERSUPPLY_H
#define UITL2POWERSUPPLY_H

#include <QMainWindow>
#include <qepicspv.h>
#include <QThread>

#include <widgets/tl2_ps_widget.h>
#include <widgets/tl2_corrector_widget.h>

namespace Ui {
class uiTL2PowerSupply;
}

class uiTL2PowerSupply : public QMainWindow
{
    Q_OBJECT

public:
    explicit uiTL2PowerSupply(QWidget *parent = 0);
    ~uiTL2PowerSupply();

private:
    Ui::uiTL2PowerSupply *ui;
    QString pv_names[17] = {"TL2-PS-CR1:enable", "TL2-PS-CR2:enable", "TL2-PS-CR3:enable", "TL2-PS-CR4:enable", "TL2-PS-CR5:enable",
                            "TL2-PS-BM1-X:enable", "TL2-PS-BM1-Y:enable", "TL2-PS-BM2-X:enable", "TL2-PS-BM2-Y:enable",
                            "TL2-PS-Q1:enable", "TL2-PS-Q2:enable", "TL2-PS-Q3:enable", "TL2-PS-Q4:enable", "TL2-PS-Q5:enable",
                            "TL2-PS-Q6:enable", "TL2-PS-Q7:enable",
                            "TL2-PS-THS:enable"};
};

#endif // UITL2POWERSUPPLY_H
