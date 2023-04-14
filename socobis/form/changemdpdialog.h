#ifndef CHANGEMDPDIALOG_H
#define CHANGEMDPDIALOG_H

#include <QDialog>

namespace Ui {
class ChangeMdpDialog;
}

class ChangeMdpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeMdpDialog(QWidget *parent = nullptr);
    ~ChangeMdpDialog();

private slots:
    void on_pushButton_clicked();

    void on_new_mdp_textChanged(const QString &arg1);

    void on_new_mdp_2_textChanged(const QString &arg1);

private:
    Ui::ChangeMdpDialog *ui;
};

#endif // CHANGEMDPDIALOG_H
