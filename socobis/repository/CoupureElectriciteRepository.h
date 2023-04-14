#ifndef COUPUREELECTRICITEREPOSITORY_H
#define COUPUREELECTRICITEREPOSITORY_H

#include <QSqlQuery>
#include <QList>
#include <QSqlError>
#include "models/coupureElectricite.h"

namespace CoupureElectriciteRepository {
QList<CoupureElectricite> getAll();

CoupureElectricite getOneById(int id);

QSqlError addOne(CoupureElectricite c);

}

#endif // COUPUREELECTRICITEREPOSITORY_H
