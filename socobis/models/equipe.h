#ifndef EQUIPE_H
#define EQUIPE_H
#include<QString>
#include <QDate>

class Rotation{
public:
    Rotation(){};
    int id_equipe_jour;
    int id_equipe_nuit;
    QDate debut;
    int duration;
    void permute(){
        int id = id_equipe_jour;
        id_equipe_jour = id_equipe_nuit;
        id_equipe_nuit = id;
    }
};

class Equipe
{
public:
    Equipe(){};
    int id=0;
    QString name;
    bool is_tour;
    QString rotation;
    QDate date_debut;
    int duration;
};

#endif // EQUIPE_H
