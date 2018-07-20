#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>

// Select here the right DB driver for Qt
#define DRIVER "QSQLITE"

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseManager(QObject *parent = nullptr);
    void execute(QSqlQuery query);

private:
    QSqlDatabase database;
};

#endif // DATABASEMANAGER_H
