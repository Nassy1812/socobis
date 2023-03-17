#ifndef TABLEAUBORDCONTROLLER_H
#define TABLEAUBORDCONTROLLER_H

#include <QWidget>

namespace Ui {
class TableauBordController;
}

class TableauBordController : public QWidget
{
    Q_OBJECT

public:
    explicit TableauBordController(QWidget *parent = nullptr);
    ~TableauBordController();

private:
    Ui::TableauBordController *ui;
};

#endif // TABLEAUBORDCONTROLLER_H
