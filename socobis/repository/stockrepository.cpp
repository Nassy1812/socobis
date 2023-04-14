#include "stockrepository.h"
#include <QSqlQuery>
#include <QDateTime>
#include "repository/MarchandiseRepository.h"
///Entrant 0 Sortant 1
QSqlError StockRepository::addStock(Stock s){
    QSqlQuery q;
    q.prepare("INSERT INTO stocks(date,type,id_marchandise,quantite) VALUES(?,?,?,?)");
    q.addBindValue(QDateTime::currentDateTime());
    q.addBindValue(s.type);
    q.addBindValue(s.id_marchandise);
    q.addBindValue(s.quantite);
    if(!q.exec())
        return q.lastError();
    return QSqlError();
}
QList<Stock> StockRepository::getIn(){
    QList<Stock> s;
    QSqlQuery q;
    q.prepare("SELECT * FROM stocks WHERE type=? ORDER BY date DESC");
    q.addBindValue(0);
    q.exec();
    while(q.next()){
        Stock c;
        c.date = q.value("date").toDateTime();
        c.id = q.value("id").toInt();
        c.id_marchandise = q.value("id_marchandise").toInt();
        c.quantite = q.value("quantite").toInt();
        c.type =0;
        c.marchandise = MarchandiseRepository::getOneById(c.id_marchandise);
        s.append(c);
    }

    return s;
}
QList<Stock> StockRepository::getOut(){
    QList<Stock> s;
    QSqlQuery q;
    q.prepare("SELECT * FROM stocks WHERE type=? ORDER BY date DESC");
    q.addBindValue(1);
    q.exec();
    while(q.next()){
        Stock c;
        c.date = q.value("date").toDateTime();
        c.id = q.value("id").toInt();
        c.id_marchandise = q.value("id_marchandise").toInt();
        c.quantite = q.value("quantite").toInt();
        c.type =1;
        c.marchandise = MarchandiseRepository::getOneById(c.id_marchandise);
        s.append(c);
    }
    return s;
}
QList<Stock> StockRepository::getAll(){
    QList<Stock> s;
    QSqlQuery q;
    q.prepare("SELECT * FROM stocks");
    q.addBindValue(1);
    q.exec();
    while(q.next()){
        Stock c;
        c.date = q.value("date").toDateTime();
        c.id = q.value("id").toInt();
        c.id_marchandise = q.value("id_marchandise").toInt();
        c.quantite = q.value("quantite").toInt();
        c.type =q.value("type").toInt();
        c.marchandise = MarchandiseRepository::getOneById(c.id_marchandise);
        s.append(c);
    }
    return s;
}
