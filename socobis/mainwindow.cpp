#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "model.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    ui->statusbar->hide();

    if(!model::initDb()){
        QMessageBox::critical(this,
                                       "Socobis",
                                       "Le fichier socobis.db est introuvale, "
                                       "Réinstaller le logiciel peut corriger cette erreur");
        qApp->exit();

    }

    //Instantiation des controllers
    machineController = new MachineController;
    tabController = new TableauBordController;
    panneAnalyseController = new PanneAnalyseController;
    panneHistoryController = new PanneHistoriqueController;
    personnelController = new PersonnelController;
    stockController = new StockController;

   //Controller par défaut
    ui->contentLayout->addWidget(tabController);
    actualContent = tabController;

    //connect(ui->machineBtn, SIGNAL(rightClicked(QPoint)), this, SLOT(on_machineBtn_rightClicked(QPoint)));

    showMaximized();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setContent(QWidget *widget){
    actualContent->hide();
    ui->contentLayout->replaceWidget(actualContent,widget);
    actualContent = widget;
    actualContent->show();
}


void MainWindow::on_bordBtn_clicked()
{
    setContent(tabController);
}


void MainWindow::on_machineBtn_clicked()
{
    setContent(machineController);
}


void MainWindow::on_storyBtn_clicked()
{
    setContent(panneHistoryController);
}


void MainWindow::on_persBtn_clicked()
{
    setContent(personnelController);
}


void MainWindow::on_analyseBtn_clicked()
{
    setContent(panneAnalyseController);
}


void MainWindow::on_stockBtn_clicked()
{
    setContent(stockController);
}



