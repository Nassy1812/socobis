#include "InterventionRepository.h"
#include "models/intervention.h"
#include "PanneRepository.h"
#include "EquipeRepository.h"


QSqlError InterventionRepository::addOne(Intervention i){
    QSqlQuery q;
    q.prepare("INSERT INTO interventions(date,id_panne,id_equipe,description) "
              "VALUES(?,?,?,?)");
    q.addBindValue(i.date);
    q.addBindValue(i.id_panne);
    q.addBindValue(i.id_equipe);
    q.addBindValue(i.description);
    if(!q.exec())
        return q.lastError();
    return QSqlError();
}

QList<Intervention> InterventionRepository::getAll(){
    QList<Intervention> ints;
    QSqlQuery q;
    q.exec("SELECT * FROM iterventions");
    while(q.next()){
        Intervention i;
        i.date = q.value("date").toDateTime();
        i.description = q.value("description").toString();
        i.id_equipe = q.value("id_equipe").toInt();
        i.id_panne = q.value("id_panne").toInt();
        i.equipe = EquipeRepository::getOnebyId(i.id_equipe);
        i.panne = PanneRepository::getOneById(i.id_panne);
        ints.append(i);
    }
    return ints;
}

Intervention InterventionRepository::getOneById(int id){
    Intervention i;
    QSqlQuery q;
    q.prepare("SELECT * FROM iterventions WHERE id=?");
    q.addBindValue(id);
    q.exec();
    if(q.first()){
        i.date = q.value("date").toDateTime();
        i.description = q.value("description").toString();
        i.id_equipe = q.value("id_equipe").toInt();
        i.id_panne = q.value("id_panne").toInt();
        i.equipe = EquipeRepository::getOnebyId(i.id_equipe);
        i.panne = PanneRepository::getOneById(i.id_panne);
    }
    return i;
}
