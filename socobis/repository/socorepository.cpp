#include "socorepository.h"
#include <QSqlQuery>
#include <QCryptographicHash>

QString SocoRepository::hashMdp(QString mdp){
    QByteArray data = mdp.toUtf8();
    QByteArray md5 = QCryptographicHash::hash(data,QCryptographicHash::Md5);
    return QString(md5);
}

QSqlError SocoRepository::changeMdp(QString newMdp,QString mail){
    QString md5 = hashMdp(newMdp);
    QSqlQuery q;
    q.prepare("UPDATE socobis SET mdp=?, mail=?");
    q.addBindValue(md5);
    q.addBindValue(mail);
    if(!q.exec())
        return q.lastError();
    return QSqlError();
}

bool SocoRepository::valideMdp(QString mdp){
    mdp = hashMdp(mdp);
    QSqlQuery q;
    q.prepare("SELECT * FROM socobis WHERE mdp=?");
    q.addBindValue(mdp);
    q.exec();
    if(q.first())
        return true;
    return false;
}
