#include "tableaubordcontroller.h"
#include "ui_tableaubordcontroller.h"
#include "repository/PanneRepository.h"
#include "Form/addpannedialog.h"
#include "repository/machinerepository.h"
#include "repository/EnsembleRepository.h"
#include "repository/sousEnsembleRepository.h"
#include "repository/PieceRepository.h"
#include "repository/MarchandiseRepository.h"
#include "repository/CoupureElectriciteRepository.h"
#include "Form/addcoupuredialog.h"
#include "Form/changemdpdialog.h"

#include <QPrintDialog>
#include <QPrinter>

#include <QPushButton>

TableauBordController::TableauBordController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableauBordController)
{
    ui->setupUi(this);
    ui->beginDate->setDate(QDateTime::currentDateTime().date().addYears(-1));
    ui->endDate->setDate(QDateTime::currentDateTime().date());
    ui->date_spin->setValue(QDate::currentDate().year());
    updateView();
}

void TableauBordController::updateView(){
    updateTable();
    filterInvTable();
    updateInvTable();
    updateCharts();
    updateElecTable();
}

void TableauBordController::updateElecTable(){
    QList<CoupureElectricite> coupures = CoupureElectriciteRepository::getAll();

    int y = ui->date_spin->value();
    for(int m=1;m<=12;m++){
        QDateTime debut_mois(QDate(y,m,1),QTime());
        QDateTime fin_mois = debut_mois.addMonths(1).addDays(-1);
        qint64 duree_total=0;
        qint64 consommation=0;
        qint64 montant=0;

        foreach (CoupureElectricite c, coupures) {
            // Vérification si la coupure est dans le mois donné
            if(c.date_fin >= debut_mois && c.date_debut <= fin_mois){
                // Calcul de la durée de la coupure qui se trouve dans le mois
                QDateTime debut = (c.date_debut <= debut_mois) ? debut_mois: c.date_debut;
                QDateTime fin = (c.date_fin <= fin_mois) ? c.date_fin : fin_mois;
                qint64 duration = debut.secsTo(fin);
                duree_total+=duration;
                consommation+=c.consommation;
                montant += c.consommation * c.montant;
            }

        }
        int rest = duree_total % 3600;
        int hour = (duree_total-rest)/3600;
        int min = rest/60;


        QLabel *d = new QLabel(QString::number(hour)+" heure(s) "+QString::number(min)+" minutes");
        QLabel *c = new QLabel(QString::number(consommation));
        QLabel *mt = new QLabel(QString::number(montant));

        d->setAlignment(Qt::AlignHCenter);
        c->setAlignment(Qt::AlignHCenter);
        mt->setAlignment(Qt::AlignHCenter);

        ui->coupureTable->setCellWidget(m-1,1,d);
        ui->coupureTable->setCellWidget(m-1,2,c);
        ui->coupureTable->setCellWidget(m-1,3,mt);
    }
    qint64 montant_year = 0;
    foreach (CoupureElectricite c, coupures) {
        //Vérification si le coupure est dans l'année
        if(c.date_fin.date().year() >= y && c.date_debut.date().year()<= y){
            montant_year += (c.consommation * c.montant);
        }
    }
    ui->montant_edit->setText(QString::number(montant_year) + " Ariary");
    ui->coupureTable->resizeColumnsToContents();
}

TableauBordController::~TableauBordController()
{
    delete ui;
}

void TableauBordController::openEditor(int id){
    addPanneDialog *d = new addPanneDialog(id,this);
    d->show();
    connect(d,&QDialog::finished,this,[=](){
       updateTable();
    });
}

void TableauBordController::updateCharts(){
    updateMaintenabilite();
    updateFiabilite();
    updateIndisponibilite();
}
void TableauBordController::updateFiabilite(){

        QList<Machine> machines = MachineRepository::getTopPanne(4);
        QStringList categories;
//        categories << "Machine1" << "Machine2" << "Machine3" << "Machine4";

        QBarSet *cumul = new QBarSet("Cumul(%)");
        QBarSet *resteFiabilite = new QBarSet("Reste de fiabilité(%)");
        resteFiabilite->setColor(QColor::fromRgb(255, 175, 0));

//        *cumul << 9 << 2 << 7 << 5;
//        *resteFiabilite << 5 << 1 << 6 << 8;s
        int d4 = 0;
        int b=0;
        foreach(Machine m, machines){
            d4+=m.nombre_panne;
            categories << m.name;
        }
        int d=0;
        foreach (Machine m, machines) {
            if(d4>0){
                d+=m.nombre_panne;
                int c = (100 * d)/d4;
                b = c - b;
                cumul->append(c);
                resteFiabilite->append(b);
            }
        }

    //![1]

    //![2]
        QBarSeries *seriesFiabilite = new QBarSeries();
        seriesFiabilite->append(cumul);
        seriesFiabilite->append(resteFiabilite);

    //![2]

    //![3]
        QChart *chartFiabilite = new QChart();
        chartFiabilite->addSeries(seriesFiabilite);
        chartFiabilite->setTitle("Fiabilité");
        chartFiabilite->setAnimationOptions(QChart::SeriesAnimations);
    //![3]

    //![4]

        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        axisX->append(categories);
        chartFiabilite->addAxis(axisX, Qt::AlignBottom);
        seriesFiabilite->attachAxis(axisX);

        QValueAxis *axisY = new QValueAxis();
        axisY->setRange(0,100);
        chartFiabilite->addAxis(axisY, Qt::AlignLeft);
        seriesFiabilite->attachAxis(axisY);
    //![4]

    //![5]
        chartFiabilite->legend()->setVisible(true);
        chartFiabilite->legend()->setAlignment(Qt::AlignBottom);
    //![5]

    //![6]
        QChartView *chartView = new QChartView(chartFiabilite);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->setGeometry(0, 0, 500, 500);

        ui->gridLayout->addWidget(chartView, 0, 0);


}
void TableauBordController::updateIndisponibilite(){
    QList<Machine> machines = MachineRepository::getTopTime(4);
    QStringList categories;
    QBarSet *cumul = new QBarSet("Cumul(%)");
    QBarSet *resteFiabilite = new QBarSet("Reste de fiabilité(%)");
    resteFiabilite->setColor(QColor::fromRgb(255, 175, 0));

    int d4 = 0;
    int b=0;
    foreach(Machine m, machines){
        d4+=m.temps_arret;
        categories << m.name;
    }
    int d=0;
    foreach (Machine m, machines) {
        if(d4>0){
            d+=m.nombre_panne;
            int c = (100 * d)/d4;
            b = c - b;
            cumul->append(c);
            resteFiabilite->append(b);
        }
    }

//![1]

//![2]
    QBarSeries *seriesMaintenabilite = new QBarSeries();
    seriesMaintenabilite->append(cumul);
    seriesMaintenabilite->append(resteFiabilite);

//![2]

//![3]
    QChart *chartMaintenabilite = new QChart();
    chartMaintenabilite->addSeries(seriesMaintenabilite);
    chartMaintenabilite->setTitle("Indisponibilité");
    chartMaintenabilite->setAnimationOptions(QChart::SeriesAnimations);
//![3]

//![4]

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chartMaintenabilite->addAxis(axisX, Qt::AlignBottom);
    seriesMaintenabilite->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0,100);
    chartMaintenabilite->addAxis(axisY, Qt::AlignLeft);
    seriesMaintenabilite->attachAxis(axisY);
//![4]

//![5]
    chartMaintenabilite->legend()->setVisible(true);
    chartMaintenabilite->legend()->setAlignment(Qt::AlignBottom);
//![5]

//![6]
    QChartView *chartView1 = new QChartView(chartMaintenabilite);
    chartView1->setRenderHint(QPainter::Antialiasing);
    chartView1->setGeometry(0, 0, 500, 500);

    ui->gridLayout->addWidget(chartView1, 0, 1);
}
void TableauBordController::updateMaintenabilite(){
    QList<Machine> machines = MachineRepository::getTopMoyen(4);
    QStringList categories;
    QBarSet *cumul = new QBarSet("Cumul(%)");
    QBarSet *resteFiabilite = new QBarSet("Reste de fiabilité(%)");
    resteFiabilite->setColor(QColor::fromRgb(255, 175, 0));

    int d4 = 0;
    int b=0;
    foreach(Machine m, machines){
        d4+=m.temps_moyen_arret;
        categories << m.name;
    }
    int d=0;
    foreach (Machine m, machines) {
        if(d4>0){
            d+=m.nombre_panne;
            int c = (100 * d)/d4;
            b = c - b;
            cumul->append(c);
            resteFiabilite->append(b);
        }
    }
//![1]

//![2]
    QBarSeries *seriesMaintenabilite = new QBarSeries();
    seriesMaintenabilite->append(cumul);
    seriesMaintenabilite->append(resteFiabilite);

//![2]

//![3]
    QChart *chartMaintenabilite = new QChart();
    chartMaintenabilite->addSeries(seriesMaintenabilite);
    chartMaintenabilite->setTitle("Maintenabilité");
    chartMaintenabilite->setAnimationOptions(QChart::SeriesAnimations);
//![3]

//![4]

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chartMaintenabilite->addAxis(axisX, Qt::AlignBottom);
    seriesMaintenabilite->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0,100);
    chartMaintenabilite->addAxis(axisY, Qt::AlignLeft);
    seriesMaintenabilite->attachAxis(axisY);
//![4]

//![5]
    chartMaintenabilite->legend()->setVisible(true);
    chartMaintenabilite->legend()->setAlignment(Qt::AlignBottom);
//![5]

//![6]
    QChartView *chartView1 = new QChartView(chartMaintenabilite);
    chartView1->setRenderHint(QPainter::Antialiasing);
    chartView1->setGeometry(0, 0, 500, 500);

    ui->gridLayout->addWidget(chartView1, 1, 0);
}

void TableauBordController::updateTable(){
//    this->updateView();
\
    QList<Panne> ps;
    pannes.clear();
    pannes = PanneRepository::getAll();

    foreach (Panne p, pannes) {
        if(p.etat != 2 && ui->beginDate->date() <= p.date_debut.date() && p.date_debut.date() <= ui->endDate->date()){
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

void TableauBordController::on_beginDate_dateChanged(const QDate &date)
{
    ui->endDate->setMinimumDate(date);
    updateTable();
}


void TableauBordController::on_endDate_dateChanged(const QDate &date)
{
    Q_UNUSED(date);
    updateTable();
}


void TableauBordController::on_newBtn_clicked()
{
    updateTable();
}


void TableauBordController::on_showInvCheck_toggled(bool checked)
{
    ui->invCombo->setEnabled(!checked);
    filterInvTable();
    updateInvTable();
}


void TableauBordController::on_invCombo_currentTextChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    filterInvTable();
    updateInvTable();
}

void TableauBordController::filterInvTable(){
    invStocks = MarchandiseRepository::getAll();
    if(!ui->showInvCheck->isChecked()){
        QList<Marchandise> newEntry;
        foreach(Marchandise m, invStocks){
            if(m.designation == ui->invCombo->currentText()){
                newEntry.append(m);
            }
        }
        invStocks.clear();
        invStocks = newEntry;
    }
}

void TableauBordController::updateInvTable(){
    ui->invtable->setRowCount(invStocks.size());
    int row=0;
    foreach (Marchandise m, invStocks) {
        QLabel *dLabel = new QLabel; //designation
        QLabel *cLabel = new QLabel; //caracteristique
        QLabel *qLabel = new QLabel; //quantite entrant
        QLabel *pLabel = new QLabel; //sortant
        QLabel *mLabel = new QLabel; //restant

        dLabel->setAlignment(Qt::AlignCenter);
        cLabel->setAlignment(Qt::AlignCenter);
        qLabel->setAlignment(Qt::AlignCenter);
        pLabel->setAlignment(Qt::AlignCenter);
        mLabel->setAlignment(Qt::AlignCenter);

        dLabel->setText(m.designation);
        cLabel->setText(m.caracteristique);
        qLabel->setText(QString::number(MarchandiseRepository::getNbIn(m.id)));
        pLabel->setText(QString::number(MarchandiseRepository::getNbOut(m.id)));
        mLabel->setText(QString::number(m.stock));

        ui->invtable->setCellWidget(row,0,dLabel);
        ui->invtable->setCellWidget(row,1,cLabel);
        ui->invtable->setCellWidget(row,2,qLabel);
        ui->invtable->setCellWidget(row,3,pLabel);
        ui->invtable->setCellWidget(row,4,mLabel);

        row++;
    }
}

void TableauBordController::on_addBtn_clicked()
{
    AddCoupureDialog *dialog = new AddCoupureDialog(this);
    dialog->open();
    connect(dialog,&QDialog::finished,this,[=](){
       updateElecTable();
    });
}


void TableauBordController::on_date_spin_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    updateElecTable();
}


void TableauBordController::on_printBtn_clicked()
{
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);

    QPrintDialog* dialog = new QPrintDialog(&printer,this);
    if(dialog->exec() == QDialog::Accepted){
        QPainter painter(&printer);
        painter.setRenderHint(QPainter::Antialiasing);

        ui->coupureTable->render(&painter);

        painter.end();
    }

}


void TableauBordController::on_pushButton_clicked()
{
    ChangeMdpDialog *dialog = new ChangeMdpDialog(this);
    dialog->open();
}

