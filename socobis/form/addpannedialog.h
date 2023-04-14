#ifndef ADDPANNEDIALOG_H
#define ADDPANNEDIALOG_H

#include <QDialog>
#include <QSpinBox>
#include <QComboBox>
#include "models/machine.h"
#include "models/panne.h"

namespace Ui {
class addPanneDialog;
}

class addPanneDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addPanneDialog(int panne_id=0,QWidget *parent = nullptr);
    ~addPanneDialog();

private slots:
    void on_etat_pieceCombo_currentIndexChanged(int index);

    void on_codeCombo_currentIndexChanged(int index);

    void on_machineCombo_currentIndexChanged(int index);

    void on_ensembleCombo_currentIndexChanged(int index);

    void on_sousCombo_currentIndexChanged(int index);

    void on_pushButton_clicked();


    void on_pushButton_2_clicked();

    void on_etatCombo_currentIndexChanged(int index);

    void on_startDate_dateChanged(const QDate &date);


private:
    Ui::addPanneDialog *ui;
    Panne m_panne;
    QComboBox* designationCombo;
    QComboBox* caracComobo;
    QSpinBox *quantiteSpin;
    void fillStockTable();
    void fillEditCombo();
    void updateView();
    QList<Machine> machines;
    void on_designationCombo_currenttextChanged(QString text);
};

#endif // ADDPANNEDIALOG_H
