#include "panneanalysecontroller.h"
#include "ui_panneanalysecontroller.h"
#include "repository/PanneRepository.h"
#include "Form/addpannedialog.h"
#include "repository/machinerepository.h"
#include "repository/EnsembleRepository.h"
#include "repository/sousEnsembleRepository.h"
#include "repository/PieceRepository.h"

#include <QPushButton>

PanneAnalyseController::PanneAnalyseController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PanneAnalyseController)
{
    ui->setupUi(this);
    ui->beginDate->setDate(QDateTime::currentDateTime().date().addYears(-1));
    ui->endDate->setDate(QDateTime::currentDateTime().date());
    updateTable();
}

void PanneAnalyseController::updateTable(){
    QList<Panne> ps;
    pannes.clear();
    pannes = PanneRepository::getAll();

    foreach (Panne p, pannes) {
        if(ui->beginDate->date() <= p.date_debut.date() && p.date_debut.date() <= ui->endDate->date()){
            ps.append(p);
        }
    }
    ui->storyTable->setRowCount(ps.size());
    int row=0;
    QLocale fr(QLocale::French);
    foreach(Panne p, ps){
        QLabel *dLab = new QLabel(fr.toString(p.date_debut,"dddd d MMMM yyyy"));
        QLabel *hLabel = new QLabel(p.date_debut.toString("hh:mm"));
        QLabel *mLabel = new QLabel(MachineRepository::getOneById(p.id_machine).name);
        QLabel *eLabel = new QLabel();
        QLabel *cLabel = new QLabel();
        QLabel *diagLabel = new QLabel(p.diagnostique);
        QLabel *iLabel = new QLabel(p.intervention);
        QLabel *rLabel = new QLabel(p.remarque);
        QPushButton *btn = new QPushButton("Modifier");

        dLab->setAlignment(Qt::AlignHCenter);
        hLabel->setAlignment(Qt::AlignHCenter);
        mLabel->setAlignment(Qt::AlignHCenter);
        eLabel->setAlignment(Qt::AlignHCenter);
        cLabel->setAlignment(Qt::AlignHCenter);
        diagLabel->setAlignment(Qt::AlignHCenter);
        iLabel->setAlignment(Qt::AlignHCenter);
        rLabel->setAlignment(Qt::AlignHCenter);

        connect(btn,&QPushButton::clicked,this,[=](){
            openEditor(p.id);
        });

        Piece piece = PieceRepository::getOneById(p.id_piece);
        Sous_ensemble sens = SousEnsembleRepository::getOneById(piece.id_sous_ensemble);
        Ensemble ens = EnsembleRepository::getOneById(sens.id_ensemble);
        eLabel->setText(ens.name+"/"+sens.name+"/"+piece.designation);
        QStringList states = {"Ouverte","En attente de pieces","Fermée"};
        qDebug()<<states.at(p.etat);
        if(p.etat != 2){
            cLabel->setText(states.at(p.etat));
        }else{
            long diff = p.date_debut.secsTo(p.date_fin);
            int rest = diff % 3600;
            int hour = (diff-rest)/3600;
            int min = rest/60;
            cLabel->setText(QString::number(hour)+"heure(s) et "+QString::number(min)+" minutes");
        }

        ui->storyTable->setCellWidget(row,0,dLab);
        ui->storyTable->setCellWidget(row,1,hLabel);
        ui->storyTable->setCellWidget(row,2,mLabel);
        ui->storyTable->setCellWidget(row,3,eLabel);
        ui->storyTable->setCellWidget(row,4,cLabel);
        ui->storyTable->setCellWidget(row,5,diagLabel);
        ui->storyTable->setCellWidget(row,6,iLabel);
        ui->storyTable->setCellWidget(row,7,rLabel);
        ui->storyTable->setCellWidget(row,8,btn);
        row++;
    }
}

void PanneAnalyseController::openEditor(int id){
    addPanneDialog *d = new addPanneDialog(id,this);
    d->show();
    connect(d,&QDialog::finished,this,[=](){
       updateTable();
    });
}

PanneAnalyseController::~PanneAnalyseController()
{
    delete ui;
}

void PanneAnalyseController::on_beginDate_dateChanged(const QDate &date)
{
    ui->endDate->setMinimumDate(date);
    updateTable();
}


void PanneAnalyseController::on_newBtn_clicked()
{
    openEditor(0);
}


void PanneAnalyseController::on_endDate_dateChanged(const QDate &date)
{
    Q_UNUSED(date);
    updateTable();
}

