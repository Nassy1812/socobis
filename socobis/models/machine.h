#ifndef MACHINE_H
#define MACHINE_H
#include<QString>
#include <QDate>
#include <QDateTime>

class Machine
{

public:
    Machine(){};
    int id;
    QString name;
    QString code;
    QString marque;
    QString annee;
    QString reference;
    int puissance;
    QString image;
    int frequence_panne;
    QDateTime date_ajout;

};

#endif // MACHINE_H
