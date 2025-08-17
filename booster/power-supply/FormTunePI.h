#ifndef FORMTUNEPI_H
#define FORMTUNEPI_H

#include <QMainWindow>

namespace Ui {
class FormTunePI;
}

class FormTunePI : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormTunePI(QString magnet, QWidget *parent = 0);
    ~FormTunePI();

private:
    Ui::FormTunePI *ui;

    QString magnet;
};

#endif // FORMTUNEPI_H
