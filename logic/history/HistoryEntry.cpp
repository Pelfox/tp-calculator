#include "HistoryEntry.h"

QSqlQuery HistoryEntry::toQuery(QSqlDatabase db) const {
    QSqlQuery query(db);
    query.prepare("INSERT INTO history (expression, result) VALUES (:expression, :result)");
    query.bindValue(":expression", this->expression);
    query.bindValue(":result", this->result);
    return query;
}

