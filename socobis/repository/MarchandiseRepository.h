#ifndef MARCHANDISEREPOSITORY_H
#define MARCHANDISEREPOSITORY_H

#include <QSqlQuery>
#include <QList>
#include <QSqlError>
#include "models/marchandise.h"

namespace MarchandiseRepository {

QSqlError addOne(Marchandise m);

QList<Marchandise> getAll();

Marchandise getOneById(int id);
}

#endif // MARCHANDISEREPOSITORY_H
