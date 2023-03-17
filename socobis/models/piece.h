#ifndef PIECE_H
#define PIECE_H
#include<QString>

#include "sous_ensemble.h"

class Piece
{
public:
    Piece(){};
    int id;
    QString name;
    int id_sous_ensemble;
    QString designation, caracteristiques, img, fiche_technique;
    Sous_ensemble sous_ensemble;
    bool is_usure;
};
#endif // PIECE_H
