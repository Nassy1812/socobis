#include "sousEnsembleRepository.h"
#include "models/machine.h"
#include "EnsembleRepository.h"
#include "models/ensemble.h"
#include "PieceRepository.h"
QSqlError SousEnsembleRepository::addOne(Sous_ensemble s){
    QSqlQuery q;
    q.prepare("INSERT INTO sous_ensembles(name,id_ensemble) VALUES(?,?)");
    q.addBindValue(s.name);
    q.addBindValue(s.id_ensemble);
    if(!q.exec())
        return q.lastError();
    return QSqlError();
}

bool SousEnsembleRepository::exists(Sous_ensemble s){
    QSqlQuery q;
    q.prepare("SELECT * FROM sous_ensembles WHERE name=? AND id_ensemble=?");
    q.addBindValue(s.name);
    q.addBindValue(s.id_ensemble);
    q.exec();
    if(q.first())
        return true;
    return false;
}

QList<Sous_ensemble> SousEnsembleRepository::getAllbyEnsembleId(int id_ensemble){
    QList<Sous_ensemble> sens;
    QSqlQuery q;
    q.prepare("SELECT * FROM sous_ensembles WHERE id_ensemble=?");
    q.addBindValue(id_ensemble);
    if(!q.exec())
        qDebug()<<q.lastError().text();
    while(q.next()){
        Sous_ensemble sen;
        sen.ensemble = EnsembleRepository::getOneById(id_ensemble);
        sen.id = q.value("id").toInt();
        sen.name = q.value("name").toString();
        sen.id_ensemble = id_ensemble;
        sens.append(sen);
    }
    return sens;
}

Sous_ensemble SousEnsembleRepository::getOneById(int id){
    QSqlQuery q;
    Sous_ensemble sen;
    q.prepare("SELECT * FROM sous_ensembles WHERE id=?");
    q.addBindValue(id);
    q.exec();
    if(q.first()){
        sen.id_ensemble = q.value("id_ensemble").toInt();
        sen.ensemble = EnsembleRepository::getOneById(sen.id_ensemble);
        sen.id = q.value("id").toInt();
        sen.name = q.value("name").toString();
    }
    return sen;
}

QSqlError SousEnsembleRepository::deleteAllInEnsemble(int id){
    QSqlQuery q;
    q.prepare("DELETE FROM sous_ensembles WHERE id_ensemble=?");
    q.addBindValue(id);
    if(!q.exec())
        return q.lastError();
    return QSqlError();
}

QSqlError SousEnsembleRepository::deleteOne(Sous_ensemble s){
//    QSqlError err = PieceRepository::deleteAllInSousEnsemble(s.id);
//    if(err.type() != QSqlError::NoError)
//        return err;
    QSqlQuery a;
    a.prepare("DELETE FROM pieces WHERE id_sous_ensemble=?");
    a.addBindValue(s.id);
    if(!a.exec())
        return a.lastError();
    QSqlQuery q;
    q.prepare("DELETE FROM sous_ensembles WHERE id=?");
    q.addBindValue(s.id);
    if(!q.exec())
        return q.lastError();
    return QSqlError();
}
