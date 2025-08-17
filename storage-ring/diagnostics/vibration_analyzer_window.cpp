#include "vibration_analyzer_window.h"
#include "ui_vibration_analyzer_window.h"

VibrationAnalyzerWindow::VibrationAnalyzerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VibrationAnalyzerWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->btnClose, &QPushButton::clicked, this, &VibrationAnalyzerWindow::close);
}

VibrationAnalyzerWindow::~VibrationAnalyzerWindow()
{
    delete ui;
}
