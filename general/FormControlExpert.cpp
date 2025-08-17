#include "FormControlExpert.h"
#include "ui_FormControlExpert.h"

bool FormPythonManager::pythonManagerOpened = false;

FormControlExpert::FormControlExpert(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FormControlExpert)
{
    ui->setupUi(this);

    this->pythonManager = NULL;
}

FormControlExpert::~FormControlExpert()
{
    delete ui;
}

void FormControlExpert::on_btnPythonManager_clicked()
{
    //OPEN_UI(pythonManager, FormPythonManager, this);
    if (!FormPythonManager::pythonManagerOpened)
    {
        FormPythonManager* pythonManager = new FormPythonManager(this);
        pythonManager->show();
    }
}

void FormControlExpert::on_btnPythonManager46_clicked()
{
    pythonManager46 = new FormPythonManager2(this);
    pythonManager46->show();
}
