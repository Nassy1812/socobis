#ifndef TABLEAUBORDCONTROLLER_H
#define TABLEAUBORDCONTROLLER_H

#include <QWidget>
#include <QList>
#include "models/panne.h"
#include "models/marchandise.h"
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>


namespace Ui {
class TableauBordController;
}

class TableauBordController : public QWidget
{
    Q_OBJECT

public:
    explicit TableauBordController(QWidget *parent = nullptr);
    ~TableauBordController();
    void updateView();

private slots:
    void on_beginDate_dateChanged(const QDate &date);

    void on_endDate_dateChanged(const QDate &date);

    void on_newBtn_clicked();

    void on_showInvCheck_toggled(bool checked);

    void on_invCombo_currentTextChanged(const QString &arg1);

    void on_addBtn_clicked();

    void on_date_spin_valueChanged(int arg1);

    void on_printBtn_clicked();

    void on_pushButton_clicked();

private:
    Ui::TableauBordController *ui;
    void updateTable();
    void openEditor(int id);
    QList<Panne> pannes;
    void updateInvTable();
    void filterInvTable();
    QList<Marchandise> invStocks;
    void updateCharts();
    void updateFiabilite();
    void updateIndisponibilite();
    void updateMaintenabilite();
    void updateElecTable();
};

#endif // TABLEAUBORDCONTROLLER_H
