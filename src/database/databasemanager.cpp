#include "databasemanager.h"

/**
 * @file databasemanager.cpp
 * @author Dylan Van Assche
 * @date 20 Jul 2018
 * @brief DatabaseManager facade constructor
 * Constructs a DatabaseManager facade to access the database using the SQL language.
 * The DatabaseManager facade makes database access in Qt abstract from the underlying database (SQLite, MySQL, ORACLE, ...).
 * Any errors during initialisation of the database are catched and logged as CRITICAL.
 */
DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent)
{
   if(QSqlDatabase::isDriverAvailable(DRIVER)) {
        database = QSqlDatabase::addDatabase(DRIVER);
        database.setDatabaseName("~/.local/share/harbour-berail/db/linked-connections.db");

        if (!database.open()) {
            qCritical() << "Connection to database failed";
        } else {
            qInfo() << "Database connection OK";
        }
    }
    else {
        qCritical() << "Missing support for SQL driver:" << DRIVER;
    }
}

/**
 * @file databasemanager.cpp
 * @author Dylan Van Assche
 * @date 20 Jul 2018
 * @brief Executes a given QSqlQuery
 * Executes the given QSqlQuery query on the active database.
 * Before the execution takes place, the connection is checked.
 * During the execution, the errors are catched and logged as CRITICAL.
 */
void DatabaseManager::execute(QSqlQuery query)
{
    if(database.isOpen() && query.exec()) {
        qInfo() << "Creating table OK:" << query;
    }
    else {
        qCritical() << "Cannot create table:" << query.lastError().text();
    }
}

