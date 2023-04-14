#ifndef ADDCOUPUREDIALOG_H
#define ADDCOUPUREDIALOG_H

#include <QDialog>

namespace Ui {
class AddCoupureDialog;
}

class AddCoupureDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddCoupureDialog(QWidget *parent = nullptr);
    ~AddCoupureDialog();

private slots:
    void on_saveBtn_clicked();

    void on_startDate_dateChanged(const QDate &date);

    void on_startTime_timeChanged(const QTime &time);

private:
    Ui::AddCoupureDialog *ui;
};

#endif // ADDCOUPUREDIALOG_H
