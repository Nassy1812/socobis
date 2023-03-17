#include "stockcontroller.h"
#include "ui_stockcontroller.h"

StockController::StockController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StockController)
{
    ui->setupUi(this);
}

StockController::~StockController()
{
    delete ui;
}
