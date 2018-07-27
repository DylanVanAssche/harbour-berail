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

#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtCore/QtGlobal>
#include <QtCore/QtDebug>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QDir>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

// Select here the right DB driver for Qt
#define DRIVER "QSQLITE"

// Singleton pattern
class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    static DatabaseManager *getInstance(const QString &path, QObject *parent = nullptr);
    bool execute(QSqlQuery &query);
    bool startTransaction();
    bool endTransaction();
    QSqlDatabase database() const;

private:
    QSqlDatabase m_database;
    explicit DatabaseManager(const QString &path, QObject *parent);
    static DatabaseManager *m_instance;
    void setDatabase(const QSqlDatabase &database);
};

#endif // DATABASEMANAGER_H