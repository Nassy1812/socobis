#include "personnelcontroller.h"
#include "ui_personnelcontroller.h"
#include "models/equipe.h"
#include "repository/EquipeRepository.h"
#include "repository/personnelrepository.h"
#include "logger.h"
#include <QTableWidgetItem>
#include <QFileDialog>
#include <QSqlError>

namespace Rotations {
  QString jour = "JOUR";
  QString nuit = "NUIT";
}

namespace PersonnelSpeciality{
    QString MEC = "mécanicien";
    QString CAO = "caoutchouter";
    QString CHA = "chaudronnier";
    QString ELC = "électricien";
    QString INS = "instrumentiste";
    QString GRA = "graisseur";
    QString EXP = "exploitant";
    QString FAB = "opérateur";
    QStringList all = {MEC,CAO,CHA,ELC,INS,GRA,EXP,FAB};
};

PersonnelController::PersonnelController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PersonnelController)
{
    ui->setupUi(this);


    QList<Equipe> equipes = EquipeRepository::getAll();
    m_rotation.debut = equipes[0].date_debut;
    m_rotation.duration = equipes[0].duration;
    m_rotation.id_equipe_jour = (equipes[0].rotation == Rotations::jour) ? equipes[0].id : equipes[1].id;
    m_rotation.id_equipe_nuit = (equipes[0].rotation == Rotations::jour) ? equipes[1].id : equipes[0].id;
    foreach (Equipe e, equipes) {
        ui->equipe_combo->addItem(e.name);
    }

    equipes.clear();
    ui->rotation_combo->addItem(Rotations::jour);
    ui->rotation_combo->addItem(Rotations::nuit);

    ui->spec_combo->addItems(PersonnelSpeciality::all);

    m_personnel.id = 0;

    ui->date_show->setDate(QDate::currentDate());
    ui->modifDate_debut->setDate(QDate::currentDate());
    emit ui->rotationModif_combo->currentTextChanged(ui->rotationModif_combo->currentText());
    emit ui->tourModif_combo->currentTextChanged(ui->tourModif_combo->currentText());
}

PersonnelController::~PersonnelController()
{
    delete ui;
}

void PersonnelController::updateTableWidget(){
    ui->tableWidget->setRowCount(this->personnels.size());
    int row=0;
    foreach (Personnel p, this->personnels) {
        QLabel *idLab = new QLabel;
        QLabel *nameLab = new QLabel;
        QLabel *specLab = new QLabel;
        QLabel *telLab = new QLabel;

        idLab->setAlignment(Qt::AlignCenter);
        nameLab->setAlignment(Qt::AlignCenter);
        specLab->setAlignment(Qt::AlignCenter);
        telLab->setAlignment(Qt::AlignCenter);

        idLab->setText(p.num_id);
        nameLab->setText(p.name);
        specLab->setText(p.speciality);
        telLab->setText(p.tel);


        QLabel *photoLabel = new QLabel;
        photoLabel->setStyleSheet({"border-image: url("+p.img+") 0 0 0 0 stretch stretch;"});
        photoLabel->setMaximumSize(40,40);

        QPushButton *editBtn = new QPushButton("Edit");
        connect(editBtn,&QPushButton::clicked,this,[=](){
            this->m_personnel = p;

            ui->tabWidget->setCurrentWidget(ui->tab_ajout);
            updateTabEdit();
        });

        ui->tableWidget->setCellWidget(row,0,idLab);
        ui->tableWidget->setCellWidget(row,1,nameLab);
        ui->tableWidget->setCellWidget(row,2,specLab);
        ui->tableWidget->setCellWidget(row,3,telLab);
        ui->tableWidget->setCellWidget(row,4,photoLabel);
        ui->tableWidget->setCellWidget(row,5,editBtn);

        row++;
    }
}

void PersonnelController::updateTabEdit(){
    ui->id_edit->setText(m_personnel.num_id);
    ui->nom_edit->setText(m_personnel.name);
    ui->tel_edit->setText(m_personnel.tel);
    ui->spec_combo->setCurrentText(m_personnel.speciality);
    this->m_personnel.equipe = EquipeRepository::getOnebyId(m_personnel.id);
    ui->equipe_combo->setCurrentText(m_personnel.equipe.name);
}

void PersonnelController::on_rotation_combo_currentTextChanged(const QString &arg1)
{
    int id = (arg1 == Rotations::nuit)? m_rotation.id_equipe_nuit : m_rotation.id_equipe_jour;
    Equipe e = EquipeRepository::getOnebyId(id);

    //ui->date_show->setDate(e.date_debut);
    ui->dateFin_show->setDate(m_rotation.debut.addDays(m_rotation.duration));
    ui->equipeEdit->setText(e.name);
    this->personnels = EquipeRepository::getPersById(e.id);
    updateTableWidget();
}

void PersonnelController::on_parcourirBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Choisir une photo d'identité","","*.png *.jpg *.jpeg");
    ui->imgLabel->setStyleSheet({"border-image: url("+fileName+") 0 0 0 0 stretch stretch;"});
    ui->imgLabel->setPixmap(QPixmap());
    m_personnel.img = fileName;
}


void PersonnelController::on_tel_edit_textChanged(const QString &arg1)
{
    if(!arg1.back().isDigit()){
        ui->tel_edit->setText(arg1.chopped(1));
        ui->state_label->setText("Le numéro de téléphone ne doit contenir que des chiffres.");
    }
}


void PersonnelController::on_nom_edit_textChanged(const QString &arg1)
{
    if(arg1.back().isDigit()){
        ui->nom_edit->setText(arg1.chopped(1));
        ui->state_label->setText("Le nom ne doit contenir que des lettres.");
    }
}


void PersonnelController::on_saveEditBtn_clicked()
{
    if(ui->id_edit->text().isEmpty()){
        ui->state_label->setText("Veuillez renseigner tous les champs s'il vous plait");
        return;
    }if(ui->nom_edit->text().size() < 3){
        ui->state_label->setText("Le nom doit avoir au moins 3 caractères.");
        return;
    }if(ui->spec_combo->currentIndex() < 0){
        ui->state_label->setText("Veuillez choisir une spécilité pour le nouveau personnel.");
        return;
    }if(ui->equipe_combo->currentIndex() < 0){
        ui->state_label->setText("Veuillez choisir une équipe pour le nouveau personnel.");
        return;
    }

    QSqlError err;
    m_personnel.name = ui->nom_edit->text();
    m_personnel.num_id = ui->id_edit->text();
    m_personnel.id_equipe = EquipeRepository::getIdByName(ui->equipe_combo->currentText());
    m_personnel.equipe = EquipeRepository::getOnebyId(m_personnel.id);
    m_personnel.speciality = ui->spec_combo->currentText();
    m_personnel.tel = ui->tel_edit->text();

    if(m_personnel.id==0){
        err = PersonnelRepository::addOne(m_personnel);
        if(err.type() == QSqlError::NoError){
            Logger::showInformationMessage(this,QString("Personnel ajouté dans l'équipe "
                                                        "du %1 avec succés").arg(ui->equipe_combo->currentText()));
            ui->tabWidget->setCurrentWidget(ui->tab_affichage);
            ui->rotation_combo->setCurrentIndex(-1);
            ui->rotation_combo->setCurrentText(m_personnel.equipe.rotation);
            updateTableWidget();
        }else{
            Logger::showFailMessage(this,err.text());
        }
    }else{
        err = PersonnelRepository::update(this->m_personnel);
        if(err.type() == QSqlError::NoError){
            Logger::showInformationMessage(this,QString("Les données du personnel "
                                                        "ont été modifiées avec succés.").arg(ui->equipe_combo->currentText()));
            ui->tabWidget->setCurrentWidget(ui->tab_affichage);
            ui->rotation_combo->setCurrentIndex(-1);
            ui->rotation_combo->setCurrentText(m_personnel.equipe.rotation);
            updateTableWidget();
        }else{
            Logger::showFailMessage(this,err.text());
        }
    }


}


void PersonnelController::on_pushButton_clicked()
{
    m_personnel = Personnel();
    m_personnel.id = 0;
    ui->tabWidget->setCurrentWidget(ui->tab_ajout);
}


void PersonnelController::on_annuleEditBtn_clicked()
{
    if(m_personnel.id==0){
        ui->tabWidget->setCurrentWidget(ui->tab_affichage);
    }else{
        updateTabEdit();
    }

}


void PersonnelController::on_date_show_dateChanged(const QDate &date)
{
    QDate changeDate;
    m_rotation = EquipeRepository::getRotationByDate(date,&changeDate);

    emit ui->rotation_combo->currentTextChanged(ui->rotation_combo->currentText());
    ui->dateFin_show->setDate(changeDate);
}


void PersonnelController::on_saveModif_btn_clicked()
{
    m_rotation.debut = ui->modifDate_debut->date();
    m_rotation.duration = ui->dureeModif_spin->value();
    int id_a = EquipeRepository::getIdByName("A");
    int id_b = EquipeRepository::getIdByName("B");
    if((ui->rotationModif_combo->currentText() == Rotations::jour &&
        ui->tourModif_combo->currentText()=="Equipe A") ||
            (ui->rotationModif_edit->text()==Rotations::jour && ui->tourModif_edit->text()=="Equipe A")){
        m_rotation.id_equipe_jour = id_a;
        m_rotation.id_equipe_nuit = id_b;
    }else{
        m_rotation.id_equipe_jour = id_b;
        m_rotation.id_equipe_nuit = id_a;
    }
    QSqlError err = EquipeRepository::update(m_rotation);
    if(err.type() == QSqlError::NoError){
        Logger::showInformationMessage(this,"Configuration des équipes mis à jour.");
        ui->tabWidget->setCurrentWidget(ui->tab_affichage);
        ui->date_show->setDate(m_rotation.debut);
        ui->rotation_combo->setCurrentIndex(-1);
        ui->rotation_combo->setCurrentText(m_personnel.equipe.rotation);
    }else{
        Logger::showFailMessage(this,err.text());
    }
}


void PersonnelController::on_dureeModif_spin_valueChanged(int arg1)
{
    ui->dateFin_modif->setDate(ui->modifDate_debut->date().addDays(arg1));
}


void PersonnelController::on_tourModif_combo_currentTextChanged(const QString &arg1)
{
    QString text = (arg1 == "Equipe A") ? "Equipe B" : "Equipe A";
    ui->tourModif_edit->setText(text);
}


void PersonnelController::on_rotationModif_combo_currentTextChanged(const QString &arg1)
{
    QString text = (arg1 == Rotations::jour) ? Rotations::nuit : Rotations::jour;
    ui->rotationModif_edit->setText(text);
}

