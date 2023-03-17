#ifndef ADDSOUSENSEMBLEDIALOG_H
#define ADDSOUSENSEMBLEDIALOG_H

#include <QDialog>

namespace Ui {
class AddSousEnsembleDialog;
}

class AddSousEnsembleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddSousEnsembleDialog(int ensemble_id,QWidget *parent = nullptr);
    ~AddSousEnsembleDialog();

private slots:
    void on_nameEdit_textChanged(const QString &arg1);

    void on_cancelBtn_clicked();

    void on_saveBtn_clicked();

private:
    Ui::AddSousEnsembleDialog *ui;
    int ensemble_id;
};

#endif // ADDSOUSENSEMBLEDIALOG_H
