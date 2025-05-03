#ifndef HISTORYDATABASE_H
#define HISTORYDATABASE_H

#include <QFile>

#include "HistoryEntry.h"

class HistoryDatabase {
public:
    explicit HistoryDatabase(const QString& fileName);
    ~HistoryDatabase();

    void addEntry(const HistoryEntry &entry) const;
    QList<HistoryEntry> getEntries() const;

private:
    QSqlDatabase db;
};

#endif //HISTORYDATABASE_H
