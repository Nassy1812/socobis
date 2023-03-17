#include "sousEnsembleRepository.h"
#include "PieceRepository.h"
QSqlError PieceRepository::addOne(Piece p){
    QSqlQuery q;
    q.prepare("INSERT INTO pieces(name,designation,caracteristiques,img,fiche_technique,is_usure,id_sous_ensemble) "
              "VALUES(?,?,?,?,?,?,?)");
    q.addBindValue(p.name);
    q.addBindValue(p.designation);
    q.addBindValue(p.caracteristiques);
    q.addBindValue(p.img);
    q.addBindValue(p.fiche_technique);
    int usure = (p.is_usure) ? 1 : 0;
    q.addBindValue(usure);
    q.addBindValue(p.id_sous_ensemble);
    if(!q.exec())
        return q.lastError();
    return QSqlError();
}

QSqlError PieceRepository::update(Piece p){
    QSqlQuery q;
    q.prepare("UPDATE pieces SET name=?,designation=?,caracteristiques=?,img=?,fiche_technique=?,is_usure=?,id_sous_ensemble=? "
              "WHERE id=?");
    q.addBindValue(p.name);
    q.addBindValue(p.designation);
    q.addBindValue(p.caracteristiques);
    q.addBindValue(p.img);
    q.addBindValue(p.fiche_technique);
    int usure = (p.is_usure) ? 1 : 0;
    q.addBindValue(usure);
    q.addBindValue(p.id_sous_ensemble);
    q.addBindValue(p.id);
    if(!q.exec())
        return q.lastError();
    return QSqlError();
}

bool PieceRepository::exists(Piece p){
    QSqlQuery q;
    q.prepare("SELECT * FROM pieces WHERE designation=? AND id_sous_ensemble=?");
    q.addBindValue(p.designation);
    q.addBindValue(p.id_sous_ensemble);
    q.exec();
    if(q.first())
        return true;
    return false;
}

QList<Piece> PieceRepository::getAllBySousEnsembleId(int id){
    QList<Piece> pieces;
    QSqlQuery q;
    q.prepare("SELECT * FROM pieces WHERE id_sous_ensemble=?");
    q.addBindValue(id);
    q.exec();
    while(q.next()){
        Piece p;
        p.id = q.value("id").toInt();
        p.id_sous_ensemble = q.value("id_sous_ensemble").toInt();
        p.sous_ensemble = SousEnsembleRepository::getOneById(p.id_sous_ensemble);
        p.name = q.value("name").toString();
        p.designation = q.value("designation").toString();
        p.caracteristiques = q.value("caracteristiques").toString();
        p.fiche_technique = q.value("fiche_technique").toString();
        p.img = q.value("img").toString();
        p.is_usure = (q.value("is_usure").toBool()) ? 1 : 0 ;
        pieces.append(p);
    }
    return pieces;
}

Piece PieceRepository::getOneById(int id){
    Piece p;
    QSqlQuery q;
    q.prepare("SELECT * FROM pieces WHERE id=?");
    q.addBindValue(id);
    q.exec();
    if(q.first()){
        p.id = q.value("id").toInt();
        p.id_sous_ensemble = q.value("id_sous_ensemble").toInt();
        p.sous_ensemble = SousEnsembleRepository::getOneById(p.id_sous_ensemble);
        p.name = q.value("name").toString();
        p.designation = q.value("designation").toString();
        p.caracteristiques = q.value("caracteristiques").toString();
        p.fiche_technique = q.value("fiche_technique").toString();
        p.img = q.value("img").toString();
        p.is_usure = (q.value("is_usure").toBool()) ? 1 : 0 ;
    }
    return p;
}

QSqlError PieceRepository::deleteAllInSousEnsemble(int id){
    QSqlQuery q;
    q.prepare("DELETE FROM pieces WHERE id_sous_ensemble=?");
    q.addBindValue(id);
    if(!q.exec())
        return q.lastError();
}

QSqlError PieceRepository::deleteOne(Piece p){
    QSqlQuery q;
    q.prepare("DELETE FROM pieces WHERE id=?");
    q.addBindValue(p.id);
    if(!q.exec())
        return q.lastError();
    return QSqlError();
}
