#ifndef STOCK_H
#define STOCK_H
#include<QDateTime>
#include<QString>

class Stock
{
public:
    Stock(){};
    int id;
    QDateTime date;
    int type; //0 if entrant, 1 if sortant
    int id_marchandise;
    int quantite;
    int prix;

};

#endif // STOCK_H
