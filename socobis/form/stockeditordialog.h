#ifndef STOCKEDITORDIALOG_H
#define STOCKEDITORDIALOG_H

#include <QDialog>

namespace Ui {
class stockEditorDialog;
}

class stockEditorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit stockEditorDialog(int index=0,QWidget *parent = nullptr);
    ~stockEditorDialog();

private slots:
    void on_typeCombo_currentTextChanged(const QString &arg1);

    void on_cancelBtn_clicked();

    void on_desCombo_currentTextChanged(const QString &arg1);

    void on_saveBtn_clicked();

    void on_carCombo_currentTextChanged(const QString &arg1);

private:
    Ui::stockEditorDialog *ui;
    QStringList designations;
    QStringList caracs;
};

#endif // STOCKEDITORDIALOG_H
