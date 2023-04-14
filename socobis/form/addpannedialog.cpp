#include "addpannedialog.h"
#include "ui_addpannedialog.h"
#include "repository/MarchandiseRepository.h"
#include "repository/machinerepository.h"
#include "repository/EnsembleRepository.h"
#include "repository/sousEnsembleRepository.h"
#include "repository/PieceRepository.h"
#include "repository/PanneRepository.h"
#include "repository/MarchandiseRepository.h"
#include "logger.h"

addPanneDialog::addPanneDialog(int panne_id,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addPanneDialog)
{
    ui->setupUi(this);
    ui->stockTable->setVisible(false);
    this->m_panne = PanneRepository::getOneById(panne_id);
    fillStockTable();
    fillEditCombo();
    connect(designationCombo,&QComboBox::currentTextChanged,this,[=](){
        on_designationCombo_currenttextChanged(designationCombo->currentText());
    });

    ui->startDate->setDateTime(QDateTime::currentDateTime());


    ui->endDate->setEnabled(ui->etatCombo->currentIndex()==2);

    if(m_panne.id !=0)
        updateView();

}

void addPanneDialog::updateView(){
    Piece p = PieceRepository::getOneById(m_panne.id_piece);
    Sous_ensemble sense = SousEnsembleRepository::getOneById(p.id_sous_ensemble);
    Ensemble e = EnsembleRepository::getOneById(sense.id_ensemble);
    Machine m = MachineRepository::getOneById(e.id_machine);
    ui->pieceCombo->setCurrentText(p.designation);
    ui->sousCombo->setCurrentText(sense.name);
    ui->ensembleCombo->setCurrentText(e.name);
    ui->machineCombo->setCurrentText(m.name);
    ui->btEdit->setText(m_panne.bon_de_travail);
    ui->intervenantCombo->setCurrentText(m_panne.intervenant);
    ui->remEdit->setText(m_panne.remarque);
    ui->detec_facCombo->setCurrentText(m_panne.facteur_de_detection);
    ui->startDate->setDateTime(m_panne.date_debut);
    ui->etatCombo->setCurrentIndex(m_panne.etat);
    ui->endDate->setDateTime(m_panne.date_fin);
    ui->diagEdit->setText(m_panne.diagnostique);
    ui->facEdit->setText(m_panne.facteur);
    ui->interventionEdit->setText(m_panne.intervention);
    ui->interTypeCombo->setCurrentText(m_panne.intervention);
    ui->etat_pieceCombo->setCurrentIndex(m_panne.etat_piece);
}

addPanneDialog::~addPanneDialog()
{
    delete ui;
}

void addPanneDialog::on_etat_pieceCombo_currentIndexChanged(int index)
{
    ui->stockTable->setVisible(index==1);
}

void addPanneDialog::fillStockTable(){


    ui->stockTable->setRowCount(1);
    designationCombo = new QComboBox;
    caracComobo = new QComboBox;
    quantiteSpin = new QSpinBox;

    quantiteSpin->setMinimum(1);
    designationCombo->addItems(MarchandiseRepository::getDesignations());
    caracComobo->addItems(MarchandiseRepository::getCharacterics(designationCombo->currentText()));

    ui->stockTable->setCellWidget(0,0,designationCombo);
    ui->stockTable->setCellWidget(0,1,caracComobo);
    ui->stockTable->setCellWidget(0,2,quantiteSpin);
    if(m_panne.id != 0){
        //inchangee=0 à changer=1
        ui->etat_pieceCombo->setCurrentIndex(m_panne.etat_piece);
        if(m_panne.etat_piece == 1){

            designationCombo->setCurrentText(PieceRepository::getOneById(m_panne.id_piece).designation);
            caracComobo->setCurrentText(PieceRepository::getOneById(m_panne.id_piece).caracteristiques);
            quantiteSpin->setValue(m_panne.quantite);
        }
//        designationCombo->setCurrentText(m_panne.d)
    }
}

void addPanneDialog::on_designationCombo_currenttextChanged(QString text){
    caracComobo->clear();
    caracComobo->addItems(MarchandiseRepository::getCharacterics(text));
}

void addPanneDialog::fillEditCombo(){
    machines = MachineRepository::getAll();
    foreach (Machine m, machines) {
        ui->codeCombo->addItem(m.code,m.id);
        ui->machineCombo->addItem(m.name,m.id);
    }
}

void addPanneDialog::on_codeCombo_currentIndexChanged(int index)
{
    int id = ui->codeCombo->itemData(index).toInt();
    ui->machineCombo->setCurrentIndex(index);
    QList<Ensemble> ens = EnsembleRepository::getAllByMachineId(id);
    ui->ensembleCombo->clear();
    foreach (Ensemble e, ens) {
        ui->ensembleCombo->addItem(e.name,e.id);
    }
}


void addPanneDialog::on_machineCombo_currentIndexChanged(int index)
{
    int id = ui->machineCombo->itemData(index).toInt();
    ui->codeCombo->setCurrentIndex(index);
    QList<Ensemble> ens = EnsembleRepository::getAllByMachineId(id);
    ui->ensembleCombo->clear();
    foreach (Ensemble e, ens) {
        ui->ensembleCombo->addItem(e.name,e.id);
    }
}


void addPanneDialog::on_ensembleCombo_currentIndexChanged(int index)
{
    int id = ui->ensembleCombo->itemData(index).toInt();
    QList<Sous_ensemble> sens = SousEnsembleRepository::getAllbyEnsembleId(id);
    ui->sousCombo->clear();
    foreach(Sous_ensemble e, sens){
        ui->sousCombo->addItem(e.name,e.id);
    }
}


void addPanneDialog::on_sousCombo_currentIndexChanged(int index)
{
    int id = ui->sousCombo->itemData(index).toInt();
    QList<Piece> pieces = PieceRepository::getAllBySousEnsembleId(id);
    ui->pieceCombo->clear();
    foreach(Piece p, pieces){
        ui->pieceCombo->addItem(p.name,p.id);
    }
}


void addPanneDialog::on_pushButton_clicked()
{
    Panne p;
    p.date_debut = ui->startDate->dateTime();
    p.date_fin = ui->endDate->dateTime();
    p.id_machine = ui->machineCombo->itemData(ui->machineCombo->currentIndex()).toInt();
    p.id_piece = ui->pieceCombo->itemData(ui->pieceCombo->currentIndex()).toInt();
    p.bon_de_travail = ui->btEdit->text();
    p.intervenant = ui->intervenantCombo->currentText();
    p.remarque = ui->remEdit->toPlainText();
    p.facteur_de_detection = ui->detec_facCombo->currentText();
    p.etat = ui->etatCombo->currentIndex();
    p.diagnostique = ui->diagEdit->toPlainText();
    p.facteur = ui->facEdit->toPlainText();
    p.intervention = ui->interventionEdit->toPlainText();
    p.type_intervention = ui->interTypeCombo->currentText();
    p.etat_piece = ui->etat_pieceCombo->currentIndex();
    p.id = m_panne.id;
    if(p.etat_piece == 1){//Piece changee
        Marchandise m = MarchandiseRepository::getByDesignationAndCharacteristics(designationCombo->currentText(),
                                                                                  caracComobo->currentText());
        MarchandiseRepository::add(m,-quantiteSpin->value());
        Logger::showInformationMessage(this,QString::number(quantiteSpin->value())+" "+
                                       m.designation+"de "+m.caracteristique+" ont été débité(s) avec succès");
        p.quantite = quantiteSpin->value();
    }
    if(p.id ==0){
        QSqlError err = PanneRepository::addOne(p);
        if(err.type() == QSqlError::NoError){
            Logger::showInformationMessage(this,"La panne a été ajoutée avec succès");
        }else{
            Logger::showFailMessage(this,err.text());
        }
        Machine m = MachineRepository::getOneById(p.id_machine);
        err = MachineRepository::addPanne(m);
    }else{
        QSqlError err = PanneRepository::update(p);
        if(err.type() == QSqlError::NoError){
            Logger::showInformationMessage(this,"Les modifications ont été enregistrées avec succès");
        }else{
            Logger::showFailMessage(this,err.text());
        }
        Panne x = PanneRepository::getOneById(p.id);
        if(x.etat != 2 && ui->etatCombo->currentIndex() == 2){
            Machine m = MachineRepository::getOneById(p.id_machine);
            err = MachineRepository::addStopTime(m,p);
        }

    }
    close();
}


void addPanneDialog::on_pushButton_2_clicked()
{
    close();
}


void addPanneDialog::on_etatCombo_currentIndexChanged(int index)
{
    ui->endDate->setEnabled(index==2);
}


void addPanneDialog::on_startDate_dateChanged(const QDate &date)
{
    ui->endDate->setMinimumDate(date);
}



