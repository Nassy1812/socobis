#include "addpiecedialog.h"
#include "ui_addpiecedialog.h"
#include "repository/EnsembleRepository.h"
#include "repository/sousEnsembleRepository.h"
#include "repository/machinerepository.h"
#include "repository/PieceRepository.h"
#include <QFileDialog>
#include "logger.h"

AddPieceDialog::AddPieceDialog(int sous_ensemble_id,int piece_id,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPieceDialog)
{
    ui->setupUi(this);
    setWindowFlag(Qt::Widget);
    this->sous_ensemble_id = sous_ensemble_id;
    Sous_ensemble sens = SousEnsembleRepository::getOneById(sous_ensemble_id);
    Ensemble ens = EnsembleRepository::getOneById(sens.id_ensemble);
    Machine mach = MachineRepository::getOneById(ens.id_machine);

    ui->nomMachine->setText(mach.name);
    ui->codeMachine->setText(mach.code);
    ui->nomEnsemble->setText(ens.name);
    ui->codeEnsemble->setText(sens.name);
    ui->AjouterBtn->setEnabled(false);
    this->piece.id = piece_id;
    if(this->piece.id !=0){
        this->piece = PieceRepository::getOneById(piece_id);
        ui->photoPiece->setStyleSheet({"border-image: url("+this->piece.img+") 0 0 0 0 stretch stretch;"});
        ui->usureRadio->setChecked(this->piece.is_usure);
        ui->nomPiece->setText(this->piece.designation);
        ui->caracteristique->setText(this->piece.caracteristiques);
        ui->ficheTechnique->setPlainText(this->piece.fiche_technique);
    }

}

AddPieceDialog::~AddPieceDialog()
{
    delete ui;
}


void AddPieceDialog::on_parcourirBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Choisir une photo pour la pièce","",
                                                    "Fichiers images(*.png *.jpg *.jpeg)");
    ui->photoPiece->setStyleSheet({"border-image: url("+fileName+") 0 0 0 0 stretch stretch;"});
    piece.img = fileName;
}


void AddPieceDialog::on_annulerBtn_clicked()
{
    reject();
}


void AddPieceDialog::on_AjouterBtn_clicked()
{

    piece.name = ui->nomPiece->text();
    piece.caracteristiques = ui->caracteristique->text();
    piece.fiche_technique = ui->ficheTechnique->toPlainText();
    piece.designation = piece.name;
    piece.id_sous_ensemble = this->sous_ensemble_id;
    piece.is_usure = ui->usureRadio->isChecked();
    QSqlError err;
    if(this->piece.id == 0){
        if(PieceRepository::exists(piece)){
            Logger::showInformationMessage(this,QString("La pièce %1 existe déja dans cet sous-ensemble.").arg(piece.designation));
            return;
        }
        err = PieceRepository::addOne(piece);
        if(err.type() == QSqlError::NoError){
            Logger::showInformationMessage(this,"Pièce ajoutée avec succès");
            accept();
        }else{
            Logger::showFailMessage(this,err.text());
            reject();
        }
    }else{
        err = PieceRepository::update(piece);
        if(err.type() == QSqlError::NoError){
            Logger::showInformationMessage(this,"Pièce modifiée avec succès");
        }else{
            Logger::showFailMessage(this,err.text());
            reject();
        }
    }
}


void AddPieceDialog::on_nomPiece_textChanged(const QString &arg1)
{
    ui->AjouterBtn->setEnabled(ui->nomPiece->text().size()>1 &&
                               ui->caracteristique->text().size()>1 &&
                               ui->ficheTechnique->toPlainText().size()>1);
}


void AddPieceDialog::on_caracteristique_textChanged(const QString &arg1)
{
    ui->AjouterBtn->setEnabled(ui->nomPiece->text().size()>1 &&
                               ui->caracteristique->text().size()>1 &&
                               ui->ficheTechnique->toPlainText().size()>1);
}


void AddPieceDialog::on_ficheTechnique_textChanged()
{
    ui->AjouterBtn->setEnabled(ui->nomPiece->text().size()>1 &&
                               ui->caracteristique->text().size()>1 &&
                               ui->ficheTechnique->toPlainText().size()>1);
}

