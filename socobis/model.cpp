#include "model.h"
#include <QFile>
#include <QtSql>

bool model::initDb(){
    bool dbExists = QFile::exists("socobis.db");

    if(!dbExists)
        return false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("socobis.db");
    if(!db.open()){
        qDebug()<<"Cannot open database";
        return false;
    }
    return true;
}
