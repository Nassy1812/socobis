#ifndef MACHINECONTROLLER_H
#define MACHINECONTROLLER_H

#include <QMainWindow>
#include "models/machine.h"
#include "util/custombutton.h"
#include <QListWidgetItem>
#include "form/addensembledialog.h"

namespace Ui {
class MachineController;
}

class MachineController : public QWidget
{
    Q_OBJECT

public:
    explicit MachineController(QWidget *parent = nullptr);
    ~MachineController();



private slots:
    void showMachine(int id);
    void showMachine(Machine m);
    void showAddSetMenu(CustomButton *btn, QPoint pos);
    void showAddSubSetMenu(CustomButton *btn, QPoint pos);
    void showAddPieceMenu(CustomButton *btn, QPoint pos);
    void addEnsemble();
    void addSousEnsemble(int id_ensemble);
    void addPiece(int id_sous_ensemble);


    void on_saveBtn_clicked();

    void on_editCheck_toggled(bool checked);

    void on_addBtn_clicked();

    void on_browseBtn_clicked();

private:
    Ui::MachineController *ui;
    void updateView();
    Machine actualMachine;
    QString fileName;
    void updateTreeWidget();
    AddEnsembleDialog *addEnsembleDialog;
    void deleteMachine(int id);
    void deleteEnsemble(int id);
    void deleteSousEnsemble(int id);
    void deletePiece(int id);


};

#endif // MACHINECONTROLLER_H
