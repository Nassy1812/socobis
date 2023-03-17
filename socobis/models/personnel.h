#ifndef PERSONNEL_H
#define PERSONNEL_H
#include<QDateTime>
#include<QString>

#include "equipe.h"



class Personnel
{
public:
    Personnel(){};
    int id;
    QString name;
    QDateTime EntryDate;
    QString tel;
    QString img;
    QString speciality;
    int id_equipe;
    Equipe equipe;
    QString num_id;
};

#endif // PERSONNEL_H
