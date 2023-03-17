#include "MarchandiseRepository.h"
QSqlError MarchandiseRepository::addOne(Marchandise m){
    QSqlQuery q;
    q.prepare("INSERT INTO marchandises(designation,stock,prix_unite) "
              "VALUES(?,?,?)");
    q.addBindValue(m.designation);
    q.addBindValue(m.stock);
    q.addBindValue(m.prix_unite);
    if(!q.exec())
        return q.lastError();
    return QSqlError();
}

QList<Marchandise> MarchandiseRepository::getAll(){
    QList<Marchandise> marchandises;
    QSqlQuery q;
    q.exec("SELECT * FROM marchandises");
    while(q.next()){
        Marchandise m;
        m.designation = q.value("designation").toString();
        m.stock = q.value("stock").toInt();
        m.prix_unite = q.value("prix_unite").toInt();
        marchandises.append(m);
    }
    return marchandises;
}

Marchandise MarchandiseRepository::getOneById(int id){
    Marchandise m;
    QSqlQuery q;
    q.prepare("SELECT * FROM marchandises WHERE id=?");
    q.addBindValue(id);
    q.exec();
    if(q.next()){
        m.designation = q.value("designation").toString();
        m.stock = q.value("stock").toInt();
        m.prix_unite = q.value("prix_unite").toInt();
    }
    return m;
}
