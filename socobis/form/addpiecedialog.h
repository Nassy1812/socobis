#ifndef ADDPIECEDIALOG_H
#define ADDPIECEDIALOG_H

#include <QDialog>
#include "models/piece.h"

namespace Ui {
class AddPieceDialog;
}

class AddPieceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddPieceDialog(int sous_ensemble_id,int piece_id=0,QWidget *parent = nullptr);
    ~AddPieceDialog();

private slots:

    void on_parcourirBtn_clicked();

    void on_annulerBtn_clicked();

    void on_AjouterBtn_clicked();

    void on_nomPiece_textChanged(const QString &arg1);

    void on_caracteristique_textChanged(const QString &arg1);

    void on_ficheTechnique_textChanged();

private:
    Ui::AddPieceDialog *ui;
    int sous_ensemble_id;
    Piece piece;

};

#endif // ADDPIECEDIALOG_H
