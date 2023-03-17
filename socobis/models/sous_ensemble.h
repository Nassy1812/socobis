#ifndef SOUS_ENSEMBLE_H
#define SOUS_ENSEMBLE_H
#include<QString>

#include "ensemble.h"

class Sous_ensemble
{
public:
    Sous_ensemble(){};
    int id;
    QString name;
    int id_ensemble;
    Ensemble ensemble;

};

#endif // SOUS_ENSEMBLE_H
