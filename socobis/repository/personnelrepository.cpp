#include "personnelrepository.h"
#include <QSqlQuery>


QSqlError PersonnelRepository::addOne(Personnel p){
    QSqlQuery q;
    q.prepare("INSERT INTO personnels(name,entryDate,tel,img,speciality,id_equipe,num_id) "
              "VALUES(?,?,?,?,?,?,?)");
    q.addBindValue(p.name);
    q.addBindValue(QDateTime::currentDateTime());
    q.addBindValue(p.tel);
    q.addBindValue(p.img);
    q.addBindValue(p.speciality);
    q.addBindValue(p.id_equipe);
    q.addBindValue(p.num_id);
    if(!q.exec())
        return q.lastError();
    return QSqlError();
}
QSqlError PersonnelRepository::deleteOne(int id){
    QSqlQuery q;
    if(!q.exec(QString("DELETE FROM personnels WHERE id=%1").arg(id)))
        return q.lastError();
    return QSqlError();
}

bool PersonnelRepository::telExists(QString tel){
    QSqlQuery q;
    q.exec(QString("SELECT * FROM personnels WHERE tel=%1").arg(tel));
    if(q.first())
        return true;
    return false;
}

bool PersonnelRepository::nameExists(QString name){
    QSqlQuery q;
    q.exec(QString("SELECT * FROM personnels WHERE name=%1").arg(name));
    if(q.first())
        return true;
    return false;
}

bool PersonnelRepository::num_idExists(QString num_id){
    QSqlQuery q;
    q.exec(QString("SELECT * FROM personnels WHERE num_id=%1").arg(num_id));
    if(q.first())
        return true;
    return false;
}

QSqlError PersonnelRepository::changeEquipe(Personnel p){
    QSqlQuery q;
    q.prepare("UPDATE personnels SET equipe_id=? WHERE id=?");
    q.addBindValue(p.id_equipe);
    q.addBindValue(p.id);
    if(!q.exec())
        return q.lastError();
    return QSqlError();
}

QSqlError PersonnelRepository::update(Personnel p){
    QSqlQuery q;
    q.prepare("UPDATE personnels SET name=?,entryDate=?,tel=?,img=?,speciality=?,id_equipe=?,num_id=?"
              " WHERE id=?");
    q.addBindValue(p.name);
    q.addBindValue(QDateTime::currentDateTime());
    q.addBindValue(p.tel);
    q.addBindValue(p.img);
    q.addBindValue(p.speciality);
    q.addBindValue(p.id_equipe);
    q.addBindValue(p.num_id);
    q.addBindValue(p.id);
    if(!q.exec())
        return q.lastError();
    return QSqlError();
}
