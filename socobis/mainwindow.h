#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "controller/machinecontroller.h"
#include "controller/tableaubordcontroller.h"
#include "controller/panneanalysecontroller.h"
#include "controller/pannehistoriquecontroller.h"
#include "controller/personnelcontroller.h"
#include "controller/stockcontroller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_bordBtn_clicked();

    void on_machineBtn_clicked();

    void on_storyBtn_clicked();

    void on_persBtn_clicked();

    void on_analyseBtn_clicked();

    void on_stockBtn_clicked();

private:
    Ui::MainWindow *ui;
    void setContent(QWidget *widget);
    QWidget* actualContent;
    MachineController *machineController;
    TableauBordController *tabController;
    PanneAnalyseController *panneAnalyseController;
    PanneHistoriqueController *panneHistoryController;
    PersonnelController *personnelController;
    StockController *stockController;
};
#endif // MAINWINDOW_H
