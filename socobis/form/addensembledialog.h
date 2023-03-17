#ifndef ADDENSEMBLEDIALOG_H
#define ADDENSEMBLEDIALOG_H

#include <QDialog>

namespace Ui {
class AddEnsembleDialog;
}

class AddEnsembleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddEnsembleDialog(int machine_id, QWidget *parent = nullptr);
    ~AddEnsembleDialog();

private slots:
    void on_nameEdit_textChanged(const QString &arg1);

    void on_saveBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::AddEnsembleDialog *ui;
    int machine_id;
};

#endif // ADDENSEMBLEDIALOG_H
