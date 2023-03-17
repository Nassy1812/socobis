#include "PieceRepository.h"
#include "machinerepository.h"
#include "PanneRepository.h"
QSqlError PanneRepository::addOne(Panne p){
    QSqlQuery q;
    q.prepare("INSERT INTO pannes(date_debut, date_fin, id_machine, is_resolved, id_piece) "
              "VALUES(?,?,?,?,?)");
    q.addBindValue(p.date_debut);
    q.addBindValue(p.date_fin);
    q.addBindValue(p.id_machine);
    int res = (p.is_resolved) ? 1 : 0;
    q.addBindValue(res);
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
        p.is_resolved = (q.value("is_resolved").toInt() == 1) ? true : false;
        if(p.id_piece)
            p.piece = PieceRepository::getOneById(p.id_piece);
        p.machine = MachineRepository::getOneById(p.id_machine);
        pannes.append(p);
    }
    return pannes;
}

Panne PanneRepository::getOneById(int id){
    Panne p;
    QSqlQuery q;
    q.prepare("SELECT * FROM pannes WHERE id=?");
    q.addBindValue(id);
    q.exec();
    if(q.first()){
        p.date_debut = q.value("date_debut").toDateTime();
        p.date_fin = q.value("date_fin").toDateTime();
        p.id_machine = q.value("id_machine").toInt();
        p.id_piece = q.value("id_piece").toInt();
        p.is_resolved = (q.value("is_resolved").toInt() == 1) ? true : false;
    }
    return p;
}
