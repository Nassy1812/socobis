#ifndef MACHINEREPOSITORY_H
#define MACHINEREPOSITORY_H

#include "models/machine.h"
#include <QSqlQuery>
#include <QSqlError>


namespace MachineRepository {

QSqlError addOne(Machine m);
QSqlError update(Machine m);
QList<Machine> getAll();
Machine getOneById(int id);
QSqlError deleteOne(Machine m);
}

#endif // MACHINEREPOSITORY_H
