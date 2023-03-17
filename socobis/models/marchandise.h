#ifndef MARCHANDISE_H
#define MARCHANDISE_H
#include<QString>

class Marchandise
{
public:
    Marchandise(){};
    int id;
    QString designation;
    int prix_unite;
    int stock;

};

#endif // MARCHANDISE_H
