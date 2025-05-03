#include "HistoryDatabase.h"

#include <QSqlError>
#include <QSqlQuery>

HistoryDatabase::HistoryDatabase(const QString& fileName) {
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        this->db = QSqlDatabase::database("qt_sql_default_connection");
    } else {
        this->db = QSqlDatabase::addDatabase("QSQLITE");
    }

    this->db.setDatabaseName(fileName);
    if (!this->db.open()) {
        qCritical() << "Failed to open database" << this->db.lastError().text();
        return;
    }

    QSqlQuery query(this->db);
    if (!query.exec("CREATE TABLE IF NOT EXISTS history ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "expression TEXT NOT NULL, "
                    "result REAL NOT NULL, "
                    "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP)")) {
        qCritical() << "Failed to create table" << this->db.lastError().text();
        return;
    }
}

HistoryDatabase::~HistoryDatabase() {
    if (this->db.isOpen()) {
        this->db.close();
    }
}

void HistoryDatabase::addEntry(const HistoryEntry &entry) const {
    QSqlQuery query = entry.toQuery(this->db);
    if (!query.exec()) {
        qCritical() << "Failed to add entry" << this->db.lastError().text();
    }
}

QList<HistoryEntry> HistoryDatabase::getEntries() const {
    QList<HistoryEntry> entries;
    QSqlQuery query(this->db);
    if (!query.exec("SELECT expression, result, timestamp FROM history ORDER BY timestamp DESC")) {
        qCritical() << "Failed to get entries" << this->db.lastError().text();
        return entries;
    }

    while (query.next()) {
        const QString expression = query.value(0).toString();
        const double result = query.value(1).toDouble();
        const QString timestamp = query.value(2).toString();
        entries.append(HistoryEntry(expression, result, timestamp));
    }

    return entries;
}