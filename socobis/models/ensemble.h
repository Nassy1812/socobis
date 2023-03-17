#ifndef ENSEMBLE_H
#define ENSEMBLE_H
#include<QString>

#include "machine.h"

class Ensemble
{
public:
    Ensemble(){};
    int id;
    QString name;
    int id_machine;
    Machine machine;
};

#endif // ENSEMBLE_H

