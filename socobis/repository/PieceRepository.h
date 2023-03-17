#ifndef PIECEREPOSITORY_H
#define PIECEREPOSITORY_H


#include "models/piece.h"
#include <QSqlQuery>
#include <QSqlError>

namespace PieceRepository {

QSqlError addOne(Piece p);

QList<Piece> getAllBySousEnsembleId(int id);

Piece getOneById(int id);
bool exists(Piece p);
QSqlError deleteOne(Piece p);
QSqlError deleteAllInSousEnsemble(int id);
QSqlError update(Piece p);
}

#endif // PIECEREPOSITORY_H
