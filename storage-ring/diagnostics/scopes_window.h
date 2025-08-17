#ifndef SCOPES_WINDOW_H
#define SCOPES_WINDOW_H

#include <QMainWindow>

namespace Ui {
class ScopesWindow;
}

class ScopesWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ScopesWindow(QString title, QStringList channels, QStringList aliases, QWidget *parent = nullptr);
    ~ScopesWindow();

private:
    Ui::ScopesWindow *ui;
};

#endif // SCOPES_WINDOW_H
