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

QStringList getCharacterics(QString designation);
QStringList getDesignations();
Marchandise getByDesignationAndCharacteristics(QString designation,QString characteristics);
void add(Marchandise m, int quantite);
int getNbIn(int id);
int getNbOut(int id);
}

#endif // MARCHANDISEREPOSITORY_H
