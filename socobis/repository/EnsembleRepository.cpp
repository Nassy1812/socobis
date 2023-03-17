#include "EnsembleRepository.h"
#include "machinerepository.h"
#include "sousEnsembleRepository.h"
QList<Ensemble> EnsembleRepository::getAllByMachineId(int machineId){
    QList<Ensemble> ens;
    QSqlQuery q;
    q.prepare("SELECT * FROM ensembles WHERE id_machine=?");
    q.addBindValue(machineId);
    q.exec();
    while(q.next()){
        Ensemble e;
        e.id = q.value("id").toInt();
        e.id_machine = q.value("id_machine").toInt();
        e.machine = MachineRepository::getOneById(e.id_machine);
        e.name = q.value("name").toString();
        ens.append(e);
    }
    return ens;
}

bool EnsembleRepository::exists(Ensemble e){
    QSqlQuery q;
    q.prepare("SELECT * FROM ensembles WHERE name=? AND id_machine=?");
    q.addBindValue(e.name);
    q.addBindValue(e.id_machine);
    q.exec();
    if(q.first())
        return true;
    return false;
}

Ensemble EnsembleRepository::getOneById(int id){
    QSqlQuery q;
    Ensemble e;
    q.prepare("SELECT * FROM ensembles WHERE id=?");
    q.addBindValue(id);
    q.exec();
    if(q.first()){
        e.id = q.value("id").toInt();
        e.id_machine = q.value("id_machine").toInt();
        e.machine = MachineRepository::getOneById(e.id_machine);
        e.name = q.value("name").toString();
    }
    return e;
}

QSqlError EnsembleRepository::update(Ensemble e){
    QSqlQuery q;
    q.prepare("UPDATE ensembles SET name=? WHERE id=?");
    q.addBindValue(e.name);
    q.addBindValue(e.id);
    if(!q.exec())
        return q.lastError();
    return QSqlError();
}

QSqlError EnsembleRepository::addOne(Ensemble e){
    QSqlQuery q;
    q.prepare("INSERT INTO ensembles(id_machine,name) VALUES(?,?)");
    q.addBindValue(e.id_machine);
    q.addBindValue(e.name);
    if(!q.exec())
        return q.lastError();
    return QSqlError();
}

QSqlError EnsembleRepository::deleteAllInMachine(int id){
    QSqlQuery q;
    q.prepare("DELETE FROM ensembles WHERE id_machine=?");
    q.addBindValue(id);
    if(!q.exec())
        return q.lastError();
    return QSqlError();
}

QSqlError EnsembleRepository::deleteOne(Ensemble e){
    QList<Sous_ensemble> sens = SousEnsembleRepository::getAllbyEnsembleId(e.id);

    foreach (Sous_ensemble s, sens) {
        QSqlError err = SousEnsembleRepository::deleteOne(s);
        if(err.type() != QSqlError::NoError)
            return err;
    }
    QSqlQuery q;
    q.prepare("DELETE FROM ensembles WHERE id=?");
    q.addBindValue(e.id);
    if(!q.exec())
        return q.lastError();
    return QSqlError();
}

