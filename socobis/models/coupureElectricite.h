#ifndef COUPUREELECTRICITE_H
#define COUPUREELECTRICITE_H

#include <QDateTime>

class CoupureElectricite{
public:
    CoupureElectricite(){};
    int id;
    QDateTime date_debut;
    QDateTime date_fin;
    int consommation;
    int montant;
};

#endif // COUPUREELECTRICITE_H
