#ifndef PANNEHISTORIQUECONTROLLER_H
#define PANNEHISTORIQUECONTROLLER_H

#include <QWidget>

namespace Ui {
class PanneHistoriqueController;
}

class PanneHistoriqueController : public QWidget
{
    Q_OBJECT

public:
    explicit PanneHistoriqueController(QWidget *parent = nullptr);
    ~PanneHistoriqueController();

private:
    Ui::PanneHistoriqueController *ui;
};

#endif // PANNEHISTORIQUECONTROLLER_H
