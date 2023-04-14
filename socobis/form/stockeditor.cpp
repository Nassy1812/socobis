#include "stockeditor.h"
#include "ui_stockeditor.h"
#include "repository/MarchandiseRepository.h"
#include "logger.h"
#include "models/stock.h"
#include "repository/stockrepository.h"
#include <QString>
StockEditor::StockEditor(int index,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StockEditor)
{
    ui->setupUi(this);
    setWindowFlag(Qt::Window);
    designations = MarchandiseRepository::getDesignations();
    ui->desCombo->addItems(designations);
    ui->typeCombo->setCurrentIndex(index);
    emit ui->typeCombo->currentTextChanged(ui->typeCombo->currentText());
}

StockEditor::~StockEditor()
{
    delete ui;
}

void StockEditor::on_typeCombo_currentTextChanged(const QString &arg1)
{
    if(arg1 == "Entrant"){
        ui->desCombo->setEditable(true);
        ui->carCombo->setEditable(true);
        ui->priceSpin->setVisible(true);
        ui->label_6->setVisible(true);
    }else{
        ui->desCombo->setEditable(false);
        ui->carCombo->setEditable(false);
        ui->priceSpin->setVisible(false);
        ui->label_6->setVisible(false);
    }
}


void StockEditor::on_desCombo_currentTextChanged(const QString &arg1)
{
    if(designations.contains(arg1)){
        ui->carCombo->clear();
        caracs.clear();
        caracs = MarchandiseRepository::getCharacterics(arg1);
        ui->carCombo->addItems(caracs);
    }
}




void StockEditor::on_saveBtn_clicked()
{
    if(designations.contains(ui->desCombo->currentText()) && caracs.contains(ui->carCombo->currentText())){
        int type;
         Marchandise m = MarchandiseRepository::getByDesignationAndCharacteristics(ui->desCombo->currentText(),ui->carCombo->currentText());
        if(ui->typeCombo->currentText() == "Entrant"){
            //add stocks with a positive value
            MarchandiseRepository::add(m,ui->qSpin->value());

            Logger::showInformationMessage(this,QString(QString::number(ui->qSpin->value())+" "+
                                                        m.designation+"de "+m.caracteristique+" ont été ajouté(s) avec succès"));
            type=0;
        }else{
            //add stocks with a negative value
             MarchandiseRepository::add(m,-ui->qSpin->value());
             Logger::showInformationMessage(this,QString::number(ui->qSpin->value())+" "+
                                            m.designation+"de "+m.caracteristique+" ont été débité(s) avec succès");
             type=1;
        }
        Stock s;
        s.type = type;
        s.quantite = ui->qSpin->value();
        s.id_marchandise = m.id;
        QSqlError err  = StockRepository::addStock(s);
        if(err.type() != QSqlError::NoError)
            Logger::showFailMessage(this,err.text());
        destroy();
    }else{
        if(!ui->desCombo->currentText().isEmpty() && !ui->carCombo->currentText().isEmpty()){
            Marchandise m;
            m.designation = ui->desCombo->currentText();
            m.caracteristique = ui->carCombo->currentText();
            m.prix_unite = ui->priceSpin->value();
            m.stock = ui->qSpin->value();
            QSqlError err = MarchandiseRepository::addOne(m);
            if(err.type() == QSqlError::NoError){
                Logger::showInformationMessage(this,QString("%1 "));
                destroy();
            }else{
                Logger::showFailMessage(this,err.text());
            }
            Stock s;
            s.type = 0;
            s.quantite = ui->qSpin->value();
            m=MarchandiseRepository::getByDesignationAndCharacteristics(m.designation,m.caracteristique);
            s.id_marchandise = m.id;
            err = StockRepository::addStock(s);
            if(err.type() == QSqlError::NoError){
                Logger::showInformationMessage(this,QString(QString::number(ui->qSpin->value())+" "+
                                                            m.designation+"de "+m.caracteristique+" ont été ajouté(s) avec succès"));
                destroy();
            }else{
                Logger::showFailMessage(this,err.text());
            }
        }else{
            Logger::showFailMessage(this,"Veuillez remplir le formulaire parfaitement svp");
        }
    }
}


void StockEditor::on_cancelBtn_clicked()
{
    destroy();
}

