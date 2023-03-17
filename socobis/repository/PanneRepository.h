#ifndef PANNEREPOSITORY_H
#define PANNEREPOSITORY_H

#include <QSqlQuery>
#include<QList>
#include <QSqlError>
#include "models/panne.h"


namespace PanneRepository {

QSqlError addOne(Panne p);

QList<Panne> getAll();

Panne getOneById(int id);
}

#endif // PANNEREPOSITORY_H
