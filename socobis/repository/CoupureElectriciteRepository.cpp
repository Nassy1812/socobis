#include "CoupureElectriciteRepository.h"
QList<CoupureElectricite> CoupureElectriciteRepository::getAll(){
    QList<CoupureElectricite> coupures;
    QSqlQuery q;
    q.exec("SELECT * FROM coupure_electricite");
    while(q.next()){
        CoupureElectricite c;
        c.heure_debut = q.value("heure_debut").toDateTime();
        c.heure_fin = q.value("heure_fin").toDateTime();
        c.id = q.value("id").toInt();
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
        c.heure_debut = q.value("heure_debut").toDateTime();
        c.heure_fin = q.value("heure_fin").toDateTime();
        c.id = q.value("id").toInt();
    }
    return c;
}

QSqlError CoupureElectriciteRepository::addOne(CoupureElectricite c){
    QSqlQuery q;
    q.prepare("INSERT INTO coupure_electricite(heure_debut, heure_fin) VALUES(?,?)");
    q.addBindValue(c.heure_debut);
    q.addBindValue(c.heure_fin);
    if(!q.exec())
        return q.lastError();
    return QSqlError();
}
