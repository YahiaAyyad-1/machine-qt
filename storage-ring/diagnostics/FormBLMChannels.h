#ifndef FORMBLMCHANNELS_H
#define FORMBLMCHANNELS_H

#include <QMainWindow>

namespace Ui {
class FormBLMChannels;
}

class FormBLMChannels : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormBLMChannels(QWidget *parent = nullptr);
    ~FormBLMChannels();

private:
    Ui::FormBLMChannels *ui;
};

#endif // FORMBLMCHANNELS_H
