#ifndef STOCKREPOSITORY_H
#define STOCKREPOSITORY_H

#include "models/stock.h"
#include <QSqlError>
#include <QList>

namespace StockRepository {
   QSqlError addStock(Stock s);
   QList<Stock> getIn();
   QList<Stock> getOut();
   QList<Stock> getAll();
}

#endif // STOCKREPOSITORY_H
