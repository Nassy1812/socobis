#ifndef STOCKCONTROLLER_H
#define STOCKCONTROLLER_H

#include <QWidget>
#include "models/stock.h"
#include <QList>

namespace Ui {
class StockController;
}

class StockController : public QWidget
{
    Q_OBJECT

public:
    explicit StockController(QWidget *parent = nullptr);
    ~StockController();

private slots:
    void on_newBtn_clicked();

    void on_newBtn_2_clicked();

    void on_showInCheck_toggled(bool checked);

    void on_showOutCheck_toggled(bool checked);

    void on_showInvCheck_toggled(bool checked);

    void on_date_in_edit_valueChanged(int arg1);

    void on_date_out_edit_valueChanged(int arg1);

    void on_invCombo_currentTextChanged(const QString &arg1);

private:
    Ui::StockController *ui;
    QList<Stock> inStocks;
    QList<Stock> outStocks;
    QList<Marchandise> invStocks;
    void updateView();
    void updateInTable();
    void updateOutTable();
    void updateInvTable();
    void filterInTable();
    void filterOutTable();
    void filterInvTable();
};

#endif // STOCKCONTROLLER_H
