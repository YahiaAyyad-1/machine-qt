#ifndef VIBRATION_ANALYZER_WINDOW_H
#define VIBRATION_ANALYZER_WINDOW_H

#include <QMainWindow>

namespace Ui {
class VibrationAnalyzerWindow;
}

class VibrationAnalyzerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit VibrationAnalyzerWindow(QWidget *parent = nullptr);
    ~VibrationAnalyzerWindow();

private:
    Ui::VibrationAnalyzerWindow *ui;
};

#endif // VIBRATION_ANALYZER_WINDOW_H
