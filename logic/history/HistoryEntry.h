#ifndef HISTORYENTRY_H
#define HISTORYENTRY_H

#include <QDate>
#include <QSqlQuery>
#include <QString>
#include <utility>

class HistoryEntry {
public:
    HistoryEntry(QString expression, const double result, QString timestamp) : expression(std::move(expression)), result(result), timestamp(std::move(timestamp)) {}

    QSqlQuery toQuery(const QSqlDatabase &db) const;

    QString expression;
    double result;
    QString timestamp;
};

#endif //HISTORYENTRY_H
