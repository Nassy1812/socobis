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
    int nombre_panne;
    int temps_arret;
    int temps_moyen_arret;
};

#endif // MACHINE_H
