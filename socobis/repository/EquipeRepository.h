#ifndef EQUIPEREPOSITORY_H
#define EQUIPEREPOSITORY_H

#include <QSqlQuery>
#include <QDate>
#include "models/equipe.h"
#include "models/personnel.h"

namespace EquipeRepository {
QList<Equipe> getAll();

Equipe getOnebyId(int id);
Equipe getOneByRotation(QString rot);

QList<Personnel> getPersById(int id);

QList<Personnel> getPersByName(QString name);
int getIdByName(QString name);
Rotation getRotationByDate(QDate date, QDate *changeDate);
QSqlError update(Rotation r);
}

#endif // EQUIPEREPOSITORY_H
