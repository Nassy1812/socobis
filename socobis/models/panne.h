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
    QString bon_de_travail;
    QString intervenant;
    QString remarque;
    QString facteur_de_detection;
    int etat;
    QString diagnostique;
    QString facteur;
    QString intervention;
    QString type_intervention;
    int etat_piece;
    int quantite;

    Machine machine;
    Piece piece;
};

#endif // PANNE_H
