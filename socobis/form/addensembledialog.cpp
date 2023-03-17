#include "addensembledialog.h"
#include "ui_addensembledialog.h"
#include "repository/EnsembleRepository.h"
#include "logger.h"

AddEnsembleDialog::AddEnsembleDialog(int machine_id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEnsembleDialog)
{
    ui->setupUi(this);
    this->machine_id = machine_id;
}

AddEnsembleDialog::~AddEnsembleDialog()
{
    delete ui;
}



void AddEnsembleDialog::on_nameEdit_textChanged(const QString &arg1)
{
    ui->saveBtn->setEnabled(arg1.size()>=3);
}


void AddEnsembleDialog::on_saveBtn_clicked()
{
    QString name = ui->nameEdit->text();
    Ensemble e;
    e.name = name;
    e.id_machine = this->machine_id;
    if(EnsembleRepository::exists(e)){
        Logger::showInformationMessage(this,"Cet ensemble existe déja dans la machine");
        return;
    }
    QSqlError err = EnsembleRepository::addOne(e);
    if(err.type() == QSqlError::NoError){
        Logger::showInformationMessage(this,"Ensemble ajouté avec succès,"
                                            "Vous pouvez maintenant ajouter des sous-ensembles et des pièces");
        accept();
    }
    else{
        Logger::showFailMessage(this,err.text());
        reject();
    }
}


void AddEnsembleDialog::on_cancelBtn_clicked()
{
    reject();
}

