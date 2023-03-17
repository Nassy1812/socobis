#include "pannehistoriquecontroller.h"
#include "ui_pannehistoriquecontroller.h"

PanneHistoriqueController::PanneHistoriqueController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PanneHistoriqueController)
{
    ui->setupUi(this);
}

PanneHistoriqueController::~PanneHistoriqueController()
{
    delete ui;
}
