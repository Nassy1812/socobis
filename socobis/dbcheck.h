#ifndef DBCHECK_H
#define DBCHECK_H

#include "qdebug.h"
#include <QObject>
#include <QFile>
#include <QtSql>

class dbCheck
{
private:
    bool dbExists(){
        return QFile::exists("socobis.dll");
    }
public:
    dbCheck(QObject *parent = nullptr);

    bool openDb(){
        if(!dbExists())
            return false;
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("socobis.dll");
        if(!db.open()){
            qDebug()<<"Cannot open database";
            return false;
        }
        return true;
    }


};

#endif // DBCHECK_H
