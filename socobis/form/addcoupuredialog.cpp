#include "addcoupuredialog.h"
#include "ui_addcoupuredialog.h"
#include "repository/CoupureElectriciteRepository.h"
#include "logger.h"

AddCoupureDialog::AddCoupureDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCoupureDialog)
{
    ui->setupUi(this);
    ui->startDate->setDate(QDate::currentDate());
    ui->startTime->setTime(QTime::currentTime());
}

AddCoupureDialog::~AddCoupureDialog()
{
    delete ui;
}

void AddCoupureDialog::on_saveBtn_clicked()
{
    CoupureElectricite coupure;
    coupure.date_debut = QDateTime(ui->startDate->date(),ui->startTime->time());
    coupure.date_fin = QDateTime(ui->endDate->date(),ui->endTime->time());
    coupure.consommation = ui->conso_spin->value();
    coupure.montant = ui->prix_spin->value();

    QSqlError err = CoupureElectriciteRepository::addOne(coupure);
    if(err.type() == QSqlError::NoError){
        Logger::showInformationMessage(this,"Modificatios enregistrées avec succès");
        close();
    }else{
        Logger::showFailMessage(this,err.text());
    }
}


void AddCoupureDialog::on_startDate_dateChanged(const QDate &date)
{
    QDateTime min(date,ui->startTime->time());
    ui->endDate->setMinimumDateTime(min);
    ui->endTime->setMinimumDateTime(min);
}


void AddCoupureDialog::on_startTime_timeChanged(const QTime &time)
{
    QDateTime min(ui->startDate->date(),time);
    ui->endDate->setMinimumDateTime(min);
    ui->endTime->setMinimumDateTime(min);
}

