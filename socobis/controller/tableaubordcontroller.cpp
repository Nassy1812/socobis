#include "tableaubordcontroller.h"
#include "ui_tableaubordcontroller.h"

TableauBordController::TableauBordController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableauBordController)
{
    ui->setupUi(this);
}

TableauBordController::~TableauBordController()
{
    delete ui;
}
