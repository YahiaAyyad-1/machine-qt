#ifndef UITSEVENTGENERATOR_H
#define UITSEVENTGENERATOR_H

#include <QMainWindow>

namespace Ui {
class uiTSEventGenerator;
}

class uiTSEventGenerator : public QMainWindow
{
    Q_OBJECT

public:
    explicit uiTSEventGenerator(QWidget *parent = 0);
    ~uiTSEventGenerator();

private slots:
    void on_btnClose_clicked();

private:
    Ui::uiTSEventGenerator *ui;
};

#endif // UITSEVENTGENERATOR_H
