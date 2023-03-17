#ifndef COUPUREELECTRICITE_H
#define COUPUREELECTRICITE_H

#include <QDateTime>

class CoupureElectricite{
public:
    CoupureElectricite(){};
    int id;
    QDateTime heure_debut;
    QDateTime heure_fin;
};

#endif // COUPUREELECTRICITE_H
