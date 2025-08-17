#ifndef UICOOLING_H
#define UICOOLING_H

#include <QMainWindow>

namespace Ui {
class uiBOCooling;
}

class uiBOCooling : public QMainWindow
{
    Q_OBJECT

public:
    explicit uiBOCooling(QWidget *parent = 0);
    ~uiBOCooling();

private slots:
    void on_btnReset_clicked();

private:
    Ui::uiBOCooling *ui;
};

#endif // UICOOLING_H
