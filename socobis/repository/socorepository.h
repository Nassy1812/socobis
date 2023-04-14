#ifndef SOCOREPOSITORY_H
#define SOCOREPOSITORY_H

#include <QString>
#include <QSqlError>

class SocoRepository
{
public:
    static QString hashMdp(QString mdp);
    static QSqlError changeMdp(QString newMdp,QString mail=QString());
    static bool valideMdp(QString mdp);
};

#endif // SOCOREPOSITORY_H
