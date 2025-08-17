#ifndef LIBERA_SPARK_DATA_WINDOW_H
#define LIBERA_SPARK_DATA_WINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "macros.h"
#include "client.h"

namespace Ui {
class LiberaSparkDataWindow;
}

class LiberaSparkDataWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LiberaSparkDataWindow(QString prefix, QWidget *parent = nullptr);
    ~LiberaSparkDataWindow();

    void closeEvent(QCloseEvent* event);

public slots:
    void onClose();

private:
    Ui::LiberaSparkDataWindow *ui;
    QString prefix;
};

#endif // LIBERA_SPARK_DATA_WINDOW_H
