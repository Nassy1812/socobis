#include "PieceRepository.h"
#include "machinerepository.h"
#include "PanneRepository.h"
QSqlError PanneRepository::addOne(Panne p){
    QSqlQuery q;
    q.prepare("INSERT INTO pannes(date_debut, date_fin, id_machine,id_piece,bon_de_travail,intervenant,"
              "remarque,facteur_de_detection,etat,diagnostique,facteur,intervention,type_intervention,etat_piece,quantite) "
              "VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
    q.addBindValue(p.date_debut);
    q.addBindValue(p.date_fin);
    q.addBindValue(p.id_machine);
//    int res = (p.is_resolved) ? 1 : 0;
//    q.addBindValue(res);
    q.addBindValue(p.id_piece);
    q.addBindValue(p.bon_de_travail);
    q.addBindValue(p.intervenant);
    q.addBindValue(p.remarque);
    q.addBindValue(p.facteur_de_detection);
    q.addBindValue(p.etat);
    q.addBindValue(p.diagnostique);
    q.addBindValue(p.facteur);
    q.addBindValue(p.intervention);
    q.addBindValue(p.type_intervention);
    q.addBindValue(p.etat_piece);
    q.addBindValue(p.quantite);
    if(!q.exec())
        return q.lastError();
    return QSqlError();
}

QSqlError PanneRepository::update(Panne p){
    QSqlQuery q;
    q.prepare("UPDATE pannes SET date_debut=?, date_fin=?, id_machine=?,id_piece=?,bon_de_travail=?,intervenant=?,"
              "remarque=?,facteur_de_detection=?,etat=?,diagnostique=?,facteur=?,intervention=?,type_intervention=?,etat_piece=?,quantite=? "
              "WHERE id=?");
    q.addBindValue(p.date_debut);
    q.addBindValue(p.date_fin);
    q.addBindValue(p.id_machine);
//    int res = (p.is_resolved) ? 1 : 0;
//    q.addBindValue(res);
    q.addBindValue(p.id_piece);
    q.addBindValue(p.bon_de_travail);
    q.addBindValue(p.intervenant);
    q.addBindValue(p.remarque);
    q.addBindValue(p.facteur_de_detection);
    q.addBindValue(p.etat);
    q.addBindValue(p.diagnostique);
    q.addBindValue(p.facteur);
    q.addBindValue(p.intervention);
    q.addBindValue(p.type_intervention);
    q.addBindValue(p.etat_piece);
    q.addBindValue(p.quantite);
    q.addBindValue(p.id);
    if(!q.exec())
        return q.lastError();
    return QSqlError();
}

QList<Panne> PanneRepository::getAll(){
    QList<Panne> pannes;
    QSqlQuery q;
    q.exec("SELECT * FROM pannes");
    while(q.next()){
        Panne p;
        p.date_debut = q.value("date_debut").toDateTime();
        p.date_fin = q.value("date_fin").toDateTime();
        p.id_machine = q.value("id_machine").toInt();
        p.id_piece = q.value("id_piece").toInt();
//        p.is_resolved = (q.value("is_resolved").toInt() == 1) ? true : false;
        p.bon_de_travail = q.value("bon_de_travail").toString();
        p.intervenant = q.value("intervenant").toString();
        p.remarque = q.value("remarque").toString();
        p.facteur_de_detection = q.value("facteur_de_detection").toString();
        p.etat = q.value("etat").toInt();
        p.diagnostique = q.value("diagnostique").toString();
        p.facteur = q.value("facteur").toString();
        p.intervention = q.value("intervention").toString();
        p.etat_piece = q.value("etat_piece").toInt();
        p.quantite = q.value("quantite").toInt();
        p.id = q.value("id").toInt();

        if(p.id_piece)
            p.piece = PieceRepository::getOneById(p.id_piece);
        p.machine = MachineRepository::getOneById(p.id_machine);
        pannes.append(p);
    }
    return pannes;
}

Panne PanneRepository::getOneById(int id){
    Panne p;
    p.id=0;
    QSqlQuery q;
    q.prepare("SELECT * FROM pannes WHERE id=?");
    q.addBindValue(id);
    q.exec();
    if(q.first()){
        p.date_debut = q.value("date_debut").toDateTime();
        p.date_fin = q.value("date_fin").toDateTime();
        p.id_machine = q.value("id_machine").toInt();
        p.id_piece = q.value("id_piece").toInt();
//        p.is_resolved = (q.value("is_resolved").toInt() == 1) ? true : false;
        p.bon_de_travail = q.value("bon_de_travail").toString();
        p.intervenant = q.value("intervenant").toString();
        p.remarque = q.value("remarque").toString();
        p.facteur_de_detection = q.value("facteur_de_detection").toString();
        p.etat = q.value("etat").toInt();
        p.diagnostique = q.value("diagnostique").toString();
        p.facteur = q.value("facteur").toString();
        p.intervention = q.value("intervention").toString();
        p.etat_piece = q.value("etat_piece").toInt();
        p.quantite = q.value("quantite").toInt();
        p.id = q.value("id").toInt();
    }
    return p;
}
