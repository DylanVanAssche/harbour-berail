/******************************************************************************
 * Copyright (C) 2018 by Dylan Van Assche                                     *
 *                                                                            *
 * This file is part of BeRail.                                               *
 *                                                                            *
 *   BeRail is free software: you can redistribute it and/or modify it        *
 *   under the terms of the GNU Lesser General Public License as published    *
 *   by the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                      *
 *                                                                            *
 *   BeRail is distributed in the hope that it will be useful,                *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 *   GNU Lesser General Public License for more details.                      *
 *                                                                            *
 *   You should have received a copy of the GNU Lesser General Public         *
 *   License along with BeRail.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************/

#include "databasemanager.h"

/**
 * @file databasemanager.cpp
 * @author Dylan Van Assche
 * @date 20 Jul 2018
 * @brief DatabaseManager facade constructor
 * @param QObject *parent
 * @param QString path
 * @public
 * Constructs a DatabaseManager facade to access the database using the SQL language.
 * The DatabaseManager facade makes database access in Qt abstract from the underlying database (SQLite, MySQL, ORACLE, ...).
 * Any errors during initialisation of the database are catched and logged as CRITICAL.
 */
DatabaseManager::DatabaseManager(QString path, QObject *parent)
{
    // Set parent of this QObject. When parent is destroyed, this one is automatically cleaned up too.
    this->setParent(parent);

    if(QSqlDatabase::isDriverAvailable(DRIVER)) {
        this->setDatabase(QSqlDatabase::addDatabase(DRIVER));
        this->database().setDatabaseName(path);
        qDebug() << this->database().databaseName();

        if (!this->database().open()) {
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
 * @param QSqlQuery query
 * @public
 * Executes the given QSqlQuery query on the active database.
 * Before the execution takes place, the connection is checked.
 * During the execution, the errors are catched and logged as CRITICAL.
 */
void DatabaseManager::execute(QSqlQuery query)
{
    if(this->database().isOpen() && query.exec()) {
        qDebug() << "Executing querry OK:" << query.executedQuery();
    }
    else {
        qCritical() << "Executing querry FAILED:" << query.lastError().text();
    }
}

/**
 * @file databasemanager.cpp
 * @author Dylan Van Assche
 * @date 20 Jul 2018
 * @brief Sets the QSqlDatabase database
 * @param const QSqlDatabase &database
 * @private
 * Sets the current QSqlDatabase database to the given QSqlDatabase &database.
 */
void DatabaseManager::setDatabase(const QSqlDatabase &database)
{
    m_database = database;
}

/**
 * @file databasemanager.cpp
 * @author Dylan Van Assche
 * @date 20 Jul 2018
 * @brief Gets the current QSqlDatabase database
 * @public
 * Gets the QSqlDatabase database and returns it.
 */
QSqlDatabase DatabaseManager::database() const
{
    return m_database;
}

