#include "changemdpdialog.h"
#include "ui_changemdpdialog.h"

#include "repository/socorepository.h"
#include "logger.h"

ChangeMdpDialog::ChangeMdpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeMdpDialog)
{
    ui->setupUi(this);
    ui->pushButton->setEnabled(false);
}

ChangeMdpDialog::~ChangeMdpDialog()
{
    delete ui;
}

void ChangeMdpDialog::on_pushButton_clicked()
{
    if(SocoRepository::valideMdp(ui->old_mdp->text())){
        QSqlError err = SocoRepository::changeMdp(ui->new_mdp->text(),ui->mailEdit->text());
        if(err.type() == QSqlError::NoError){
            Logger::showInformationMessage(this,
                                           "Mot de passe changé avec succès");
            close();
        }else{
            Logger::showFailMessage(this,err.text());
        }

    }else{
        Logger::showFailMessage(this,
                                "Le mot de passe saisi est incorrect. Veuillez consulter votre supérieure");
    }
}


void ChangeMdpDialog::on_new_mdp_textChanged(const QString &arg1)
{
    ui->pushButton->setEnabled(
                arg1 == ui->new_mdp_2->text() && arg1.size() > 4
                );
}


void ChangeMdpDialog::on_new_mdp_2_textChanged(const QString &arg1)
{
    ui->pushButton->setEnabled(
                arg1 == ui->new_mdp->text() && arg1.size() > 4
                );
}

