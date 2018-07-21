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

#ifndef LINKEDCONNECTIONSFACTORY_H
#define LINKEDCONNECTIONSFACTORY_H

#include <QtCore/QObject>
#include "linkedconnectionfragment.h"
#include "../network/httpmanager.h"
#include "../database/databasemanager.h"

// Factory pattern to generate Linked Connections fragments on the fly
class LinkedConnectionsFactory: public QObject
{
    Q_OBJECT
public:
    static LinkedConnectionsFactory *getInstance(const QString &path, QObject *parent = nullptr);
    LinkedConnectionFragment *getFragment(const QUrl &uri);

private:
    static LinkedConnectionsFactory *m_instance;
    HTTPManager *m_http;
    DatabaseManager *m_db;
    LinkedConnectionFragment *getFragmentFromDatabaseManager(const QUrl &uri);
    void getFragmentFromHTTPManager(const QUrl &uri);
    void initDatabase();
    explicit LinkedConnectionsFactory(QObject *parent);
    HTTPManager *http() const;
    void setHttp(HTTPManager *http);
    DatabaseManager *db() const;
    void setDb(DatabaseManager *db);
};

#endif // LINKEDCONNECTIONSFACTORY_H
