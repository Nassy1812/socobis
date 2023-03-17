#include "addsousensembledialog.h"
#include "ui_addsousensembledialog.h"
#include "repository/sousEnsembleRepository.h"
#include "logger.h"

AddSousEnsembleDialog::AddSousEnsembleDialog(int id_ensemble,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddSousEnsembleDialog)
{
    ui->setupUi(this);
    this->ensemble_id = id_ensemble;
}

AddSousEnsembleDialog::~AddSousEnsembleDialog()
{
    delete ui;
}

void AddSousEnsembleDialog::on_nameEdit_textChanged(const QString &arg1)
{
    ui->saveBtn->setEnabled(arg1.size()>=3);
}


void AddSousEnsembleDialog::on_cancelBtn_clicked()
{
    reject();
}


void AddSousEnsembleDialog::on_saveBtn_clicked()
{
    QString name = ui->nameEdit->text();
    Sous_ensemble e;
    e.name = name;
    e.id_ensemble = this->ensemble_id;
    if(SousEnsembleRepository::exists(e)){
        Logger::showInformationMessage(this,"Cet sous-ensemble existe déja dans l'ensemble concerné");
        return;
    }
    QSqlError err = SousEnsembleRepository::addOne(e);
    if(err.type() == QSqlError::NoError){
        Logger::showInformationMessage(this,"Sous-ensemble ajouté avec succès,"
                                            "Vous pouvez maintenant ajouter des sous-ensembles et des pièces");
        accept();
    }
    else{
        Logger::showFailMessage(this,err.text());
        reject();
    }
}

