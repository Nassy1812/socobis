#ifndef PANNE_H
#define PANNE_H
#include<QDateTime>
#include "machine.h"
#include "piece.h"

class Panne
{
public:
    Panne(){};
    int id;
    QDateTime date_debut;
    QDateTime date_fin;
    int id_machine;
    bool is_resolved;
    int id_piece;
    Machine machine;
    Piece piece;
};

#endif // PANNE_H
