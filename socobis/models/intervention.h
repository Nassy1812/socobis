#ifndef INTERVENTION_H
#define INTERVENTION_H
#include<QDateTime>
#include<QString>
#include "panne.h"
#include "equipe.h"

class Intervention
{
public:
    Intervention(){};
    int id;
    QDateTime date;
    int id_panne;
    int id_equipe;
    QString description;
    Panne panne;
    Equipe equipe;
};

#endif // INTERVENTION_H
