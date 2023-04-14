#ifndef STOCK_H
#define STOCK_H
#include<QDateTime>
#include<QString>
#include "models/marchandise.h"

class Stock
{
public:
    Stock(){};
    int id;
    QDateTime date;
    int type; //0 if entrant, 1 if sortant
    int id_marchandise;
    int quantite;
    Marchandise marchandise;

};

#endif // STOCK_H
