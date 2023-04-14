#include "logindialog.h"
#include "ui_logindialog.h"

#include "repository/socorepository.h"
#include "logger.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pushButton_clicked()
{
    if(valideMdp()){
        emit login_ok();

    }else{
        Logger::showFailMessage(this,
                                "Le mot de passe saisi est incorrect. Veuillez consulter votre supérieure");
    }
}

bool LoginDialog::valideMdp(){

    return SocoRepository::valideMdp(ui->mdp_edit->text());
}
