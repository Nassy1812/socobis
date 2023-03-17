#include "ui_machinecontroller.h"
#include "machinecontroller.h"
#include "repository/machinerepository.h"
#include "repository/EnsembleRepository.h"
#include "repository/sousEnsembleRepository.h"
#include "repository/PieceRepository.h"
#include "form/addensembledialog.h"
#include "logger.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QMenu>
#include "Form/addpiecedialog.h"
#include "Form/addsousensembledialog.h"
#include <QSqlError>

MachineController::MachineController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MachineController)
{
    ui->setupUi(this);

    updateView();

}

MachineController::~MachineController()
{
    delete ui;
}

void MachineController::updateView(){
    ui->machineListWidget->clear();

    QList<Machine> machines = MachineRepository::getAll();
    foreach (Machine m, machines) {
        QListWidgetItem *item = new QListWidgetItem;
        item->setData(Qt::UserRole, m.id);
        item->setFlags(Qt::ItemIsSelectable);
        CustomButton *btn = new CustomButton;
        btn->setText(m.name + " ("+m.code+")");
        btn->setFixedSize(180, 40);
        btn->setData(m.id);
        ui->machineListWidget->addItem(item);
        ui->machineListWidget->setItemWidget(item,btn);
        connect(btn,SIGNAL(btnClicked(int)),this,SLOT(showMachine(int)));
        connect(btn,SIGNAL(rightClicked(CustomButton*,QPoint)),this,SLOT(showAddSetMenu(CustomButton*,QPoint)));
    }
//    connect(ui->machineListWidget,SIGNAL(itemClicked(QListWidgetItem*)),
//            this,SLOT(on_machineListWidget_itemClicked(QListWidgetItem*)));

}

void MachineController::showAddSetMenu(CustomButton* btn, QPoint pos){
    QMenu *menu = new QMenu(btn);
    QAction *addSet = new QAction("Ajouter un ensemble");
    QAction *remove = new QAction("Supprimer la machine");
    menu->addAction(addSet);
    menu->addAction(remove);

    addEnsembleDialog = new AddEnsembleDialog(btn->getData(),this);
    connect(addSet,SIGNAL(triggered(bool)),this,SLOT(addEnsemble()));
    connect(remove,&QAction::triggered,this,[=](){
        int b = QMessageBox::warning(this,"Socobis","La suppression est irreversible, Voulez vous continuez?",
                             QMessageBox::Ok,QMessageBox::Cancel);
       if(b == QMessageBox::Ok)
           deleteMachine(btn->getData());
    });

    menu->popup(ui->machineTree->pos()+pos+btn->pos()+QPoint(0,btn->height()*2));
    //menu->popup(pos);
}

void MachineController::addEnsemble(){
    addEnsembleDialog->show();
    connect(addEnsembleDialog,&QDialog::finished,this,[=](){
        updateTreeWidget();
    });
}

void MachineController::showMachine(int id){
    Machine m = MachineRepository::getOneById(id);
    this->actualMachine = m;
    showMachine(m);
    ui->deleteBtn->setEnabled(true);
}

void MachineController::showMachine(Machine m){
        ui->nameEdit->setText(m.name);
        ui->codeEdit->setText(m.code);
        ui->powerEdit->setValue(m.puissance);
        ui->yearEdit->setValue(m.annee.toInt());
        ui->refEdit->setText(m.reference);
        ui->marqueEdit->setText(m.marque);
        ui->editFrame->show();
        ui->editCheck->setChecked(false);
        ui->imgLabel->setStyleSheet({"border-image: url("+m.image+") 0 0 0 0 stretch stretch;"});
        updateTreeWidget();
}

void MachineController::updateTreeWidget(){
    this->setCursor(Qt::WaitCursor);
    QList<Ensemble> ensembles = EnsembleRepository::getAllByMachineId(actualMachine.id);
    ui->machineTree->clear();
    if(ensembles.isEmpty()){
        QTreeWidgetItem *item = new QTreeWidgetItem;
        ui->machineTree->addTopLevelItem(item);
        QLabel *lab = new QLabel;
        lab->setText(QString("<b>La machine %1 ne contient aucun Ensemble.<br>"
                             "Faites un clic-droit sur la machine pour en ajouter.</b>").arg(actualMachine.name));
        lab->setWordWrap(false);
        lab->setTextFormat(Qt::RichText);
        ui->machineTree->setItemWidget(item,0,lab);
    }
    foreach (Ensemble e, ensembles) {
        QTreeWidgetItem *item = new QTreeWidgetItem;
        ui->machineTree->addTopLevelItem(item);
        CustomButton *itemBtn = new CustomButton;
        itemBtn->setText(e.name);
        itemBtn->setData(e.id);
        ui->machineTree->setItemWidget(item,0,itemBtn);
        QList<Sous_ensemble> sens = SousEnsembleRepository::getAllbyEnsembleId(e.id);
        connect(itemBtn,SIGNAL(rightClicked(CustomButton*,QPoint)),this,SLOT(showAddSubSetMenu(CustomButton*,QPoint)));
        foreach(Sous_ensemble s, sens){
            QTreeWidgetItem *i = new QTreeWidgetItem(item);
            CustomButton *sBtn = new CustomButton;
            sBtn->setText(s.name);
            sBtn->setData(s.id);

            ui->machineTree->setItemWidget(i,0,sBtn);
            QList<Piece> pieces = PieceRepository::getAllBySousEnsembleId(s.id);
            qDebug()<<"sous"<<s.id<<"len"<<pieces.size();
            connect(sBtn,SIGNAL(rightClicked(CustomButton*,QPoint)),this,SLOT(showAddPieceMenu(CustomButton*,QPoint)));
            foreach (Piece p, pieces) {
                QTreeWidgetItem *pItem = new QTreeWidgetItem(i);
                QPushButton *pBtn = new QPushButton;
                pBtn->setText(p.name);
                //pBtn->setData(p.id_sous_ensemble);
                ui->machineTree->setItemWidget(pItem,0,pBtn);
                connect(pBtn,&QPushButton::clicked,this,[=](){
                    AddPieceDialog *d = new AddPieceDialog(p.id_sous_ensemble,p.id,this);
                    d->show();
                    connect(d,&AddEnsembleDialog::finished,this,[=](){
                        updateTreeWidget();
                    });
                });
            }
        }
    }
    this->setCursor(Qt::ArrowCursor);
}

void MachineController::showAddSubSetMenu(CustomButton *btn, QPoint pos){
    QMenu *menu = new QMenu(this);
    QAction *a1 = new QAction("Ajouter un sous-ensemble");
    QAction *a2 = new QAction("Supprimer l'ensemble");

    menu->addAction(a1);
    menu->addAction(a2);

    connect(a1,&QAction::triggered,this,[=](){
        addSousEnsemble(btn->getData());
    });

    connect(a2,&QAction::triggered,this,[=](){
        int b = QMessageBox::warning(this,"Socobis","La suppression est irreversible, Voulez vous continuez?",
                             QMessageBox::Ok,QMessageBox::Cancel);
       if(b == QMessageBox::Ok)
           deleteEnsemble(btn->getData());
    });

    menu->popup(ui->machineTree->pos()+pos+btn->pos()+QPoint(0,btn->height()*2));
}

void MachineController::showAddPieceMenu(CustomButton *btn, QPoint pos){
    QMenu *menu = new QMenu(this);
    QAction *a1 = new QAction("Ajouter une pièce");
    QAction *a2 = new QAction("Supprimer le sous-ensemble");

    menu->addAction(a1);
    menu->addAction(a2);

    connect(a1,&QAction::triggered,this,[=](){
        addPiece(btn->getData());
    });

    connect(a2,&QAction::triggered,this,[=](){
        int b = QMessageBox::warning(this,"Socobis","La suppression est irreversible, Voulez vous continuez?",
                             QMessageBox::Ok,QMessageBox::Cancel);
       if(b == QMessageBox::Ok)
           deleteSousEnsemble(btn->getData());
    });

    menu->popup(ui->machineTree->pos()+pos+btn->pos()+QPoint(0,btn->height()*2));
}

void MachineController::deleteMachine(int id){
    Machine m = MachineRepository::getOneById(id);
    QSqlError err = MachineRepository::deleteOne(m);
    if(err.type() != QSqlError::NoError)
        Logger::showFailMessage(this,err.text());
    else
        Logger::showInformationMessage(this,"La machine et ses sous-ensmbles ont été supprimés avec succès");
    updateView();
    ui->machineTree->clear();
}
void MachineController::deleteEnsemble(int id){
    Ensemble e = EnsembleRepository::getOneById(id);
    QSqlError err = EnsembleRepository::deleteOne(e);
    if(err.type() != QSqlError::NoError)
        Logger::showFailMessage(this,err.text());
    else
        Logger::showInformationMessage(this,"L'ensemble et ses sous-ensmbles ont été supprimés avec succès");
    updateTreeWidget();
}
void MachineController::deleteSousEnsemble(int id){
    Sous_ensemble s = SousEnsembleRepository::getOneById(id);
    QSqlError err = SousEnsembleRepository::deleteOne(s);
    if(err.type() != QSqlError::NoError)
        Logger::showFailMessage(this,err.text());
    else
        Logger::showInformationMessage(this,"Le sous-ensebmle et ses pièces ont été supprimés avec succès");
    updateTreeWidget();
}
void MachineController::deletePiece(int id){
    Piece p = PieceRepository::getOneById(id);
    QSqlError err = PieceRepository::deleteOne(p);
    if(err.type() != QSqlError::NoError)
        Logger::showFailMessage(this,err.text());
    else
        Logger::showInformationMessage(this,"La pièce a été supprimée avec succès");
    updateTreeWidget();
}
void MachineController::addSousEnsemble(int id_ensemble){
    AddSousEnsembleDialog *d = new AddSousEnsembleDialog(id_ensemble,this);
    d->show();
    connect(d,&AddEnsembleDialog::finished,this,[=](){
        updateTreeWidget();
    });
}

void MachineController::addPiece(int id_sous_ensemble){
    AddPieceDialog *d = new AddPieceDialog(id_sous_ensemble,0,this);
    d->show();
    connect(d,&AddEnsembleDialog::finished,this,[=](){
        updateTreeWidget();
    });
}

void MachineController::on_saveBtn_clicked()
{
    QSqlError err;
    if(this->actualMachine.id != NULL){
        actualMachine.name = ui->nameEdit->text();
        actualMachine.code = ui->codeEdit->text();
        actualMachine.puissance = ui->powerEdit->text().toInt();
        actualMachine.annee = ui->yearEdit->text();
        actualMachine.reference = ui->refEdit->text();
        actualMachine.marque = ui->marqueEdit->text();
        actualMachine.image = fileName;
        ui->editCheck->setChecked(false);
        err = MachineRepository::update(actualMachine);
        if(err.type() == QSqlError::NoError){
            Logger::showInformationMessage(this,"Machine mis à jour avec succès");
            this->actualMachine = MachineRepository::getAll().last();
            updateView();
        }
        else{
            Logger::showFailMessage(this,err.text());
        }

    }else{
        actualMachine.name = ui->nameEdit->text();
        actualMachine.code = ui->codeEdit->text();
        actualMachine.puissance = ui->powerEdit->value();
        actualMachine.annee = QString::number(ui->yearEdit->value());
        actualMachine.reference = ui->refEdit->text();
        actualMachine.marque = ui->marqueEdit->text();
        actualMachine.image = fileName;
        ui->editCheck->setChecked(false);
        err = MachineRepository::addOne(actualMachine);
        if(err.type() == QSqlError::NoError){
            Logger::showInformationMessage(this,"Machine ajoutée dans la base de données avec succès");
            updateView();
        }
        else{
            Logger::showFailMessage(this,err.text());
        }

    }

}


void MachineController::on_editCheck_toggled(bool checked)
{
    ui->nameEdit->setReadOnly(!checked);
    ui->codeEdit->setReadOnly(!checked);
    ui->powerEdit->setReadOnly(!checked);
    ui->yearEdit->setReadOnly(!checked);
    ui->refEdit->setReadOnly(!checked);
    ui->marqueEdit->setReadOnly(!checked);
    ui->browseBtn->setEnabled(checked);
    ui->saveBtn->setEnabled(checked);
    ui->paysEdit->setReadOnly(!checked);
}


void MachineController::on_addBtn_clicked()
{
    Machine m;
    this->actualMachine = m;
    showMachine(m);
    ui->editCheck->setChecked(true);
    ui->deleteBtn->setEnabled(false);
    this->actualMachine.id = NULL;
}


void MachineController::on_browseBtn_clicked()
{
    fileName = QFileDialog::getOpenFileName(this,
                                                    "Choisir une image pour la machine","","*.png *.jpg *.jpeg");
    ui->imgLabel->setStyleSheet({"border-image: url("+fileName+") 0 0 0 0 stretch stretch;"});
}

