#include "stockcontroller.h"
#include "ui_stockcontroller.h"
#include "Form/stockeditordialog.h"
#include "repository/stockrepository.h"
#include "repository/MarchandiseRepository.h"

StockController::StockController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StockController)
{
    ui->setupUi(this);
    updateView();
    ui->tabWidget->setCurrentWidget(ui->inTab);
    ui->invCombo->addItems(MarchandiseRepository::getDesignations());
}

void StockController::updateView(){
    filterInTable();
    filterOutTable();
    filterInvTable();
    updateInvTable();
    updateInTable();
    updateOutTable();
}

void StockController::updateInvTable(){
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

void StockController::updateInTable(){
    ui->inTable->setRowCount(inStocks.size());
    int row=0;
    foreach (Stock s, inStocks) {
        QLabel *dLabel = new QLabel;
        QLabel *sLabel = new QLabel;
        QLabel *cLabel = new QLabel;
        QLabel *qLabel = new QLabel;
        QLabel *pLabel = new QLabel;
        QLabel *mLabel = new QLabel;

        sLabel->setAlignment(Qt::AlignCenter);
        dLabel->setAlignment(Qt::AlignCenter);
        cLabel->setAlignment(Qt::AlignCenter);
        qLabel->setAlignment(Qt::AlignCenter);
        pLabel->setAlignment(Qt::AlignCenter);
        mLabel->setAlignment(Qt::AlignCenter);

        dLabel->setText(s.date.toString());
        sLabel->setText(s.marchandise.designation);
        cLabel->setText(s.marchandise.caracteristique);
        qLabel->setText(QString::number(s.quantite));
        pLabel->setText(QString::number(s.marchandise.prix_unite));
        mLabel->setText(QString::number(s.quantite*s.marchandise.prix_unite));

        ui->inTable->setCellWidget(row,0,dLabel);
        ui->inTable->setCellWidget(row,1,sLabel);
        ui->inTable->setCellWidget(row,2,cLabel);
        ui->inTable->setCellWidget(row,3,qLabel);
        ui->inTable->setCellWidget(row,4,pLabel);
        ui->inTable->setCellWidget(row,5,mLabel);

        row++;
    }
}

void StockController::updateOutTable(){
    ui->outTable->setRowCount(outStocks.size());
    int row=0;
    foreach (Stock s, outStocks) {
        QLabel *dLabel = new QLabel;
        QLabel *sLabel = new QLabel;
        QLabel *cLabel = new QLabel;
        QLabel *qLabel = new QLabel;

        sLabel->setAlignment(Qt::AlignCenter);
        dLabel->setAlignment(Qt::AlignCenter);
        cLabel->setAlignment(Qt::AlignCenter);
        qLabel->setAlignment(Qt::AlignCenter);

        dLabel->setText(s.date.toString());
        sLabel->setText(s.marchandise.designation);
        cLabel->setText(s.marchandise.caracteristique);
        qLabel->setText(QString::number(s.quantite));

        ui->outTable->setCellWidget(row,0,dLabel);
        ui->outTable->setCellWidget(row,1,sLabel);
        ui->outTable->setCellWidget(row,2,cLabel);
        ui->outTable->setCellWidget(row,3,qLabel);

        row++;
    }
}

void StockController::filterOutTable(){
    outStocks = StockRepository::getOut();
    if(!ui->showOutCheck->isChecked()){ //Filter
        QList<Stock> newEntry;
         foreach (Stock s, outStocks) {
             if(s.date.date().year() == ui->date_in_edit->value())
                 newEntry.append(s);
         }
         outStocks.clear();
         outStocks = newEntry;
    }
}

void StockController::filterInTable(){
    inStocks = StockRepository::getIn();
    if(!ui->showInCheck->isChecked()){ //Filter
       QList<Stock> newEntry;
        foreach (Stock s, inStocks) {
            if(s.date.date().year() == ui->date_in_edit->value())
                newEntry.append(s);
        }
        inStocks.clear();
        inStocks = newEntry;
    }
}

void StockController::filterInvTable(){
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

StockController::~StockController()
{
    delete ui;
}

void StockController::on_newBtn_clicked()
{
    //Stock editor with ENTRANT type
    stockEditorDialog *editor = new stockEditorDialog(0);
    editor->show();

    connect(editor,&QDialog::finished,this,[=](){
        qDebug()<<"sss";
       updateView();
    });
}



void StockController::on_newBtn_2_clicked()
{
    //stock editor with SORTANT type
    stockEditorDialog *editor = new stockEditorDialog(1);
    editor->show();

    connect(editor,&QDialog::finished,this,[=](){
       updateView();
    });
}


void StockController::on_showInCheck_toggled(bool checked)
{
    ui->date_in_edit->setValue(0);
    ui->date_in_edit->setReadOnly(checked);
    filterInTable();
    updateInTable();
}


void StockController::on_showOutCheck_toggled(bool checked)
{
    ui->date_out_edit->setValue(0);
    ui->date_out_edit->setReadOnly(checked);
    filterOutTable();
    updateOutTable();
}


void StockController::on_showInvCheck_toggled(bool checked)
{
    ui->invCombo->setEnabled(!checked);
    filterInvTable();
    updateInvTable();
}


void StockController::on_date_in_edit_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    filterInTable();
    updateInTable();
}


void StockController::on_date_out_edit_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    filterOutTable();
    updateOutTable();
}


void StockController::on_invCombo_currentTextChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    filterInvTable();
    updateInvTable();
}

