#ifndef PANNEANALYSECONTROLLER_H
#define PANNEANALYSECONTROLLER_H

#include <QWidget>

namespace Ui {
class PanneAnalyseController;
}

class PanneAnalyseController : public QWidget
{
    Q_OBJECT

public:
    explicit PanneAnalyseController(QWidget *parent = nullptr);
    ~PanneAnalyseController();

private:
    Ui::PanneAnalyseController *ui;
};

#endif // PANNEANALYSECONTROLLER_H
