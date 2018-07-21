#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtGlobal>
#include <QtDebug>
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
    explicit DatabaseManager(QString path, QObject *parent = nullptr);
    void execute(QSqlQuery query);
    QSqlDatabase database() const;

private:
    QSqlDatabase m_database;
    void setDatabase(const QSqlDatabase &database);
};

#endif // DATABASEMANAGER_H
