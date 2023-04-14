#include "CoupureElectriciteRepository.h"
QList<CoupureElectricite> CoupureElectriciteRepository::getAll(){
    QList<CoupureElectricite> coupures;
    QSqlQuery q;
    q.exec("SELECT * FROM coupure_electricite");
    while(q.next()){
        CoupureElectricite c;
        c.date_debut = q.value("date_debut").toDateTime();
        c.date_fin = q.value("date_fin").toDateTime();
        c.id = q.value("id").toInt();
        c.consommation = q.value("consommation").toInt();
        c.montant = q.value("montant").toInt();
        coupures.append(c);
    }
    return coupures;
}

CoupureElectricite CoupureElectriciteRepository::getOneById(int id){
    CoupureElectricite c;
    QSqlQuery q;
    q.prepare("SELECT * FROM coupure_electricite WHERE id=?");
    q.addBindValue(id);
    q.exec();
    if(q.first()){
        c.date_debut = q.value("date_debut").toDateTime();
        c.date_fin = q.value("date_fin").toDateTime();
        c.id = q.value("id").toInt();
        c.consommation = q.value("consommation").toInt();
        c.montant = q.value("montant").toInt();
    }
    return c;
}


QSqlError CoupureElectriciteRepository::addOne(CoupureElectricite c){
    QSqlQuery q;
    q.prepare("INSERT INTO coupure_electricite(date_debut, date_fin, consommation, montant) VALUES(?,?,?,?)");
    q.addBindValue(c.date_debut);
    q.addBindValue(c.date_fin);
    q.addBindValue(c.consommation);
    q.addBindValue(c.montant);
    if(!q.exec())
        return q.lastError();
    return QSqlError();
}
