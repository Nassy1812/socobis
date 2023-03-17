#include "machinerepository.h"
#include "EnsembleRepository.h"

QSqlError MachineRepository::addOne(Machine m){
    QSqlQuery q;
    q.prepare("INSERT INTO machines(name,code, annee, date_ajout, img, marque, puissance, reference, frequence_panne) "
              "VALUES(?,?,?,?,?,?,?,?,?)");
    q.addBindValue(m.name);
    q.addBindValue(m.code);
    q.addBindValue(m.annee);
    q.addBindValue(QDateTime::currentDateTime());
    q.addBindValue(m.image);
    q.addBindValue(m.marque);
    q.addBindValue(m.puissance);
    q.addBindValue(m.reference);
    q.addBindValue(0);
    if(!q.exec())
        return q.lastError();
    return QSqlError();
}

QList<Machine> MachineRepository::getAll(){
    QList<Machine> machines;
    QSqlQuery q;
    q.exec("SELECT * FROM machines");
    while(q.next()){
        Machine m;
        m.name = q.value("name").toString();
        m.annee = q.value("annee").toString();
        m.date_ajout = q.value("date_ajout").toDateTime();
        m.frequence_panne = q.value("frequence_panne").toInt();
        m.id = q.value("id").toInt();
        m.image = q.value("img").toString();
        m.marque = q.value("marque").toString();
        m.puissance = q.value("puissance").toInt();
        m.reference = q.value("reference").toString();
        m.code = q.value("code").toString();
        machines.append(m);
    }
    return machines;
}
Machine MachineRepository::getOneById(int id){
    Machine m;
    QSqlQuery q;
    q.exec(QString("SELECT * FROM machines WHERE id=%1").arg(id));
    if(q.first()){
        m.name = q.value("name").toString();
        m.annee = q.value("annee").toString();
        m.date_ajout = q.value("date_ajout").toDateTime();
        m.frequence_panne = q.value("frequence_panne").toInt();
        m.id = q.value("id").toInt();
        m.image = q.value("img").toString();
        m.marque = q.value("marque").toString();
        m.puissance = q.value("puissance").toInt();
        m.reference = q.value("reference").toString();
        m.code = q.value("code").toString();
    }
    return m;
}

QSqlError MachineRepository::update(Machine m){
    QSqlQuery q;
    q.prepare("UPDATE machines SET name=?, annee=?, img=?, marque=?, puissance=?, reference=?, code=?"
              " WHERE id=?");
    q.addBindValue(m.name);
    q.addBindValue(m.annee);
    q.addBindValue(m.image);
    q.addBindValue(m.marque);
    q.addBindValue(m.puissance);
    q.addBindValue(m.reference);
    q.addBindValue(m.code);
    q.addBindValue(m.id);
    if(!q.exec())
        return q.lastError();
    return QSqlError();
}

QSqlError MachineRepository::deleteOne(Machine m){
    QList<Ensemble> ens = EnsembleRepository::getAllByMachineId(m.id);
    foreach (Ensemble e, ens) {
        QSqlError err = EnsembleRepository::deleteOne(e);
        if(err.type() != QSqlError::NoError)
            return err;
    }
    QSqlQuery q;
    q.prepare("DELETE FROM machines WHERE id=?");
    q.addBindValue(m.id);
    if(!q.exec())
        return q.lastError();
    return QSqlError();
}
