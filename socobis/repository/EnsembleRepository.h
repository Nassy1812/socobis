#ifndef ENSEMBLEREPOSITORY_H
#define ENSEMBLEREPOSITORY_H

#include "models/ensemble.h"
#include <QSqlQuery>
#include <QSqlError>


namespace EnsembleRepository {
QList<Ensemble> getAllByMachineId(int machineId);

Ensemble getOneById(int id);

QSqlError addOne(Ensemble e);
QSqlError update(Ensemble e);
bool exists(Ensemble e);
QSqlError deleteOne(Ensemble e);
QSqlError deleteAllInMachine(int id);
}



#endif // ENSEMBLEREPOSITORY_H
