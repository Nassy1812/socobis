#ifndef PERSONNELCONTROLLER_H
#define PERSONNELCONTROLLER_H

#include <QWidget>
#include "models/personnel.h"
#include "models/equipe.h"

namespace Ui {
class PersonnelController;
}

class PersonnelController : public QWidget
{
    Q_OBJECT

public:
    explicit PersonnelController(QWidget *parent = nullptr);
    ~PersonnelController();

private slots:
    void on_rotation_combo_currentTextChanged(const QString &arg1);

    void on_parcourirBtn_clicked();

    void on_tel_edit_textChanged(const QString &arg1);

    void on_nom_edit_textChanged(const QString &arg1);

    void on_saveEditBtn_clicked();

    void on_pushButton_clicked();

    void on_annuleEditBtn_clicked();

    void on_date_show_dateChanged(const QDate &date);

    void on_saveModif_btn_clicked();

    void on_dureeModif_spin_valueChanged(int arg1);

    void on_tourModif_combo_currentTextChanged(const QString &arg1);

    void on_rotationModif_combo_currentTextChanged(const QString &arg1);

private:
    Ui::PersonnelController *ui;
    QList<Personnel> personnels;
    void updateTableWidget();
    void updateTabEdit();
    Personnel m_personnel;
    Rotation m_rotation;
};

#endif // PERSONNELCONTROLLER_H
