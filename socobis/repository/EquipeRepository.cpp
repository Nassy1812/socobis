#include "EquipeRepository.h"
#include "models/equipe.h"
#include "models/personnel.h"
#include <QSqlError>

QList<Equipe> EquipeRepository::getAll(){
    QList<Equipe>equipes;
    QSqlQuery q;
    q.exec("SELECT * FROM equipes");
    while(q.next()){
        Equipe e;
        e.is_tour = (q.value("is_tour").toInt()==1) ?  true : false;
        e.name = q.value("name").toString();
        e.id = q.value("id").toInt();
        e.date_debut = q.value("date_debut").toDate();
        e.rotation = q.value("rotation").toString();
        e.duration = q.value("duration").toInt();
        equipes.append(e);
    }
    return equipes;
}

Equipe EquipeRepository::getOnebyId(int id){
    Equipe e;
    QSqlQuery q;
    q.prepare("SELECT * FROM equipes WHERE id=?");
    q.addBindValue(id);
    q.exec();
    if(q.first()){
        e.is_tour = (q.value("is_tour").toInt()==1) ?  true : false;
        e.name = q.value("name").toString();
        e.id = id;
        e.date_debut = q.value("date_debut").toDate();
        e.rotation = q.value("rotation").toString();
        e.duration = q.value("duration").toInt();
    }
    return e;
}

Equipe EquipeRepository::getOneByRotation(QString rot){
    Equipe e;
    QSqlQuery q;
    q.prepare("SELECT * FROM equipes WHERE rotation=?");
    q.addBindValue(rot);
    q.exec();
    if(q.first()){
        e.is_tour = (q.value("is_tour").toInt()==1) ?  true : false;
        e.name = q.value("name").toString();
        e.id = q.value("id").toInt();
        e.date_debut = q.value("date_debut").toDate();
        e.rotation = q.value("rotation").toString();
        e.duration = q.value("duration").toInt();
    }
    return e;
}

QList<Personnel> EquipeRepository::getPersById(int id){
    QList<Personnel>pers;
    QSqlQuery q;
    q.prepare("SELECT * FROM personnels WHERE id_equipe=?");
    q.addBindValue(id);
    q.exec();
    while(q.next()){
        Personnel e;
        e.EntryDate = q.value("entryDate").toDateTime();
        e.img = q.value("img").toString();
        e.name = q.value("name").toString();
        e.speciality = q.value("speciality").toString();
        e.equipe = getOnebyId(id);
        e.id_equipe = id;
        e.num_id = q.value("num_id").toString();
        e.tel = q.value("tel").toString();
        pers.append(e);
    }
    return pers;
}

int EquipeRepository::getIdByName(QString name){
    QSqlQuery q;
    q.prepare("SELECT id FROM equipes WHERE name=?");
    q.addBindValue(name);
    q.exec();
    if(q.first())
        return q.value("id").toInt();
    return 0;
}

QList<Personnel> EquipeRepository::getPersByName(QString name){
    QList<Personnel>pers;
    QSqlQuery q;
    q.prepare("SELECT * FROM personnels WHERE name=?");
    q.addBindValue(name);
    q.exec();
    while(q.next()){
        Personnel e;
        e.EntryDate = q.value("entryDate").toDateTime();
        e.img = q.value("img").toString();
        e.name = q.value("name").toString();
        e.speciality = q.value("speciality").toString();
        e.id_equipe = q.value("id_equipe").toInt();
        e.equipe = getOnebyId(e.id_equipe);
        e.num_id = q.value("num_id").toString();
        e.tel = q.value("tel").toString();
        pers.append(e);
    }
    return pers;
}

QSqlError EquipeRepository::update(Rotation r){
    QSqlQuery q;
    q.prepare("UPDATE equipes SET rotation=?, date_debut=?, duration=? WHERE "
              "id=?");
    q.addBindValue("NUIT");
    q.addBindValue(r.debut);
    q.addBindValue(r.duration);
    q.addBindValue(r.id_equipe_nuit);
    if(!q.exec())
        return q.lastError();
    QSqlQuery q1;
    q1.prepare("UPDATE equipes SET rotation=?, date_debut=?, duration=? WHERE "
              "id=?");
    q1.addBindValue("JOUR");
    q1.addBindValue(r.debut);
    q1.addBindValue(r.duration);
    q1.addBindValue(r.id_equipe_jour);
    if(!q1.exec())
        return q1.lastError();
    return QSqlError();
}

Rotation EquipeRepository::getRotationByDate(QDate date,QDate*changeDate){
    QList<Equipe> equipes = getAll();
    Rotation r;
    r.duration = equipes[0].duration;
    r.debut = equipes[0].date_debut;
    r.id_equipe_jour = (equipes[0].rotation == "JOUR") ? equipes[0].id : equipes[1].id;
    r.id_equipe_nuit = (equipes[0].rotation == "JOUR") ? equipes[1].id : equipes[0].id;
    int dayDiff = r.debut.daysTo(date);
    int m = dayDiff/r.duration;

    if(dayDiff>=0){
        *changeDate = r.debut.addDays((m+1)*r.duration);
        if(m%2!=0){
            r.permute();
        }
    }else{
        if(m%2==0){
            r.permute();
        }
    }

    return r;
}
