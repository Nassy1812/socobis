#include "MarchandiseRepository.h"
QSqlError MarchandiseRepository::addOne(Marchandise m){
    QSqlQuery q;
    q.prepare("INSERT INTO marchandises(designation,stock,prix_unite,caracteristique) "
              "VALUES(?,?,?,?)");
    q.addBindValue(m.designation);
    q.addBindValue(m.stock);
    q.addBindValue(m.prix_unite);
    q.addBindValue(m.caracteristique);
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
        m.caracteristique = q.value("caracteristique").toString();
        m.id = q.value("id").toInt();
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
        m.caracteristique = q.value("caracteristique").toString();
        m.id = id;
    }
    return m;
}

QStringList MarchandiseRepository::getCharacterics(QString designation){
    QSqlQuery q;
    QStringList caracs;
    q.prepare("SELECT DISTINCT caracteristique FROM marchandises WHERE designation=?");
    q.addBindValue(designation);
    q.exec();
    while(q.next()){
        caracs.append(q.value("caracteristique").toString());
    }
    return caracs;
}

QStringList MarchandiseRepository::getDesignations(){
    QSqlQuery q;
    QStringList caracs;
    q.prepare("SELECT DISTINCT designation FROM marchandises");
    q.exec();
    while(q.next()){
        caracs.append(q.value("designation").toString());
    }
    return caracs;
}

void MarchandiseRepository::add(Marchandise m,int quantite){
    QSqlQuery q;
    q.prepare("UPDATE marchandises SET stock=? WHERE id=?");
    q.addBindValue(m.stock+quantite);
    q.addBindValue(m.id);
    q.exec();
}


Marchandise MarchandiseRepository::getByDesignationAndCharacteristics(QString designation,QString characteristics){
    Marchandise m;
    QSqlQuery q;
    q.prepare("SELECT * FROM marchandises WHERE designation=? AND caracteristique=?");
    q.addBindValue(designation);
    q.addBindValue(characteristics);
    q.exec();
    if(q.first()){
        m.caracteristique = q.value("caracteristique").toString();
        m.designation = q.value("designation").toString();
        m.id = q.value("id").toInt();
        m.stock = q.value("stock").toInt();
        m.prix_unite = q.value("prix_unite").toInt();
    }
    return m;
}

int MarchandiseRepository::getNbIn(int id){
    int nb=0;
    QSqlQuery q;
    q.prepare("SELECT * FROM stocks WHERE type=? AND id_marchandise=?");
    q.addBindValue(0);
    q.addBindValue(id);
    q.exec();
    while(q.next()){
        nb+=q.value("quantite").toInt();
    }
    return nb;
}

int MarchandiseRepository::getNbOut(int id){
    int nb=0;
    QSqlQuery q;
    q.prepare("SELECT * FROM stocks WHERE type=? AND id_marchandise=?");
    q.addBindValue(1);
    q.addBindValue(id);
    q.exec();
    while(q.next()){
        nb+=q.value("quantite").toInt();
    }
    return nb;
}
