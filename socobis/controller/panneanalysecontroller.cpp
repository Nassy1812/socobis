#include "panneanalysecontroller.h"
#include "ui_panneanalysecontroller.h"

PanneAnalyseController::PanneAnalyseController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PanneAnalyseController)
{
    ui->setupUi(this);
}

PanneAnalyseController::~PanneAnalyseController()
{
    delete ui;
}
