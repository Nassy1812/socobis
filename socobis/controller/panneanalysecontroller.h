#ifndef PANNEANALYSECONTROLLER_H
#define PANNEANALYSECONTROLLER_H

#include <QWidget>
#include <QList>
#include "models/panne.h"

namespace Ui {
class PanneAnalyseController;
}

class PanneAnalyseController : public QWidget
{
    Q_OBJECT

public:
    explicit PanneAnalyseController(QWidget *parent = nullptr);
    ~PanneAnalyseController();

private slots:
    void on_beginDate_dateChanged(const QDate &date);

    void on_newBtn_clicked();

    void on_endDate_dateChanged(const QDate &date);

private:
    Ui::PanneAnalyseController *ui;
    QList<Panne> pannes;
    void updateTable();
    void openEditor(int id);
};

#endif // PANNEANALYSECONTROLLER_H
