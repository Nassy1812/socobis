#ifndef PERSONNELREPOSITORY_H
#define PERSONNELREPOSITORY_H

#include "models/personnel.h"
#include <QSqlError>
#include <QList>
#include <QString>

namespace PersonnelRepository {
    QSqlError addOne(Personnel p);
    QSqlError deleteOne(int id);
    QSqlError changeEquipe(Personnel p);
    QSqlError update(Personnel p);
    bool nameExists(QString name);
    bool telExists(QString tel);
    bool num_idExists(QString num_id);
}

#endif // PERSONNELREPOSITORY_H
