#ifndef SOUSENSEMBLEREPOSITORY_H
#define SOUSENSEMBLEREPOSITORY_H


#include "models/sous_ensemble.h"

#include <QSqlQuery>
#include <QSqlError>

namespace SousEnsembleRepository {

QSqlError addOne(Sous_ensemble s);

QList<Sous_ensemble> getAllbyEnsembleId(int id_ensemble);

Sous_ensemble getOneById(int id);
bool exists(Sous_ensemble s);
QSqlError deleteOne(Sous_ensemble s);
QSqlError deleteAllInEnsemble(int id);
}

#endif // SOUSENSEMBLEREPOSITORY_H
