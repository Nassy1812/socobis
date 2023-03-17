#ifndef STOCKCONTROLLER_H
#define STOCKCONTROLLER_H

#include <QWidget>

namespace Ui {
class StockController;
}

class StockController : public QWidget
{
    Q_OBJECT

public:
    explicit StockController(QWidget *parent = nullptr);
    ~StockController();

private:
    Ui::StockController *ui;
};

#endif // STOCKCONTROLLER_H
