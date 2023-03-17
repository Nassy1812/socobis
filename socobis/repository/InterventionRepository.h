#ifndef INTERVENTIONREPOSITORY_H
#define INTERVENTIONREPOSITORY_H

#include <QSqlQuery>
#include<QList>
#include <QSqlError>
#include "models/intervention.h"

namespace InterventionRepository{

QSqlError addOne(Intervention i);

QList<Intervention> getAll();

Intervention getOneById(int id);
}

#endif // INTERVENTIONREPOSITORY_H
