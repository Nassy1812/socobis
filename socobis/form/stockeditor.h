#ifndef STOCKEDITOR_H
#define STOCKEDITOR_H

#include <QWidget>

namespace Ui {
class StockEditor;
}

class StockEditor : public QWidget
{
    Q_OBJECT

public:
    explicit StockEditor(int index=0,QWidget *parent = nullptr);
    ~StockEditor();

private slots:
    void on_typeCombo_currentTextChanged(const QString &arg1);

    void on_desCombo_currentTextChanged(const QString &arg1);

    void on_saveBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::StockEditor *ui;
    QStringList designations;
    QStringList caracs;
};

#endif // STOCKEDITOR_H
