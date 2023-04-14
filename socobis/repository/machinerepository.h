#ifndef MACHINEREPOSITORY_H
#define MACHINEREPOSITORY_H

#include "models/machine.h"
#include "models/panne.h"
#include <QSqlQuery>
#include <QSqlError>


namespace MachineRepository {

QSqlError addOne(Machine m);
QSqlError update(Machine m);
QList<Machine> getAll();
Machine getOneById(int id);
QSqlError deleteOne(Machine m);
QSqlError addPanne(Machine m);
QSqlError addStopTime(Machine m,Panne p);
QList<Machine> getTopPanne(int nb);
QList<Machine> getTopTime(int nb);
QList<Machine> getTopMoyen(int nb);

}

#endif // MACHINEREPOSITORY_H
