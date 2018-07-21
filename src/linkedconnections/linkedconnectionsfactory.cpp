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

#include "linkedconnectionsfactory.h"
LinkedConnectionsFactory* LinkedConnectionsFactory::m_instance = nullptr;

LinkedConnectionsFactory::LinkedConnectionsFactory(QObject *parent): QObject(parent)
{
    // Set parent of this QObject. When parent is destroyed, this one is automatically cleaned up too.
    this->setParent(parent);
}

LinkedConnectionsFactory *LinkedConnectionsFactory::getInstance(const QString &path, QObject *parent)
{
    // Singleton pattern
    if(m_instance == nullptr) {
        qDebug() << "Generating new LinkedConnectionsFactory";
        m_instance = new LinkedConnectionsFactory(parent);
        m_instance->setDb(DatabaseManager::getInstance(path, parent));
        m_instance->setHttp(HTTPManager::getInstance(parent));
        m_instance->initDatabase();
    }
    return m_instance;
}

LinkedConnectionFragment *LinkedConnectionsFactory::getFragment(const QUrl &uri)
{
    // Tries to find the LC fragment in the DB
    LinkedConnectionFragment *fragment = nullptr;
    fragment = this->getFragmentFromDatabaseManager(uri);
    if(fragment == nullptr) {
        qDebug() << "HTTP to do";
        //fragment = this->getFragmentFromHTTPManager(uri);
    }
    return fragment;
}

LinkedConnectionFragment *LinkedConnectionsFactory::getFragmentFromDatabaseManager(const QUrl &uri)
{
    QSqlQuery query(this->db()->database());
    // Qt 5.6.3 docs: Don't use '*' in your SELECT statements to avoid size() to return undefined.
    query.prepare("SELECT "
                  "uri,"
                  "departureStationURI,"
                  "arrivalStationURI,"
                  "departureTime,"
                  "arrivalTime,"
                  "departureDelay,"
                  "arrivalDelay,"
                  "tripURI,"
                  "routeURI,"
                  "direction"
                  " FROM fragments WHERE uri = ?");
    query.addBindValue(uri.toString()); // Match URI's
    this->db()->execute(query);

    // URIs are the PRIMARY KEY, only 1 record may be returned in all cases!
    // -1 if no record has been found, see Qt 5.6.3 docs size()
    if(query.size() != 1) {
        while (query.next())
        {
            // Using the field name in overload value() is less efficient then using indexes according to the Qt 5.6.3 docs
            QUrl uri = query.value(0).toUrl();
            QUrl departureStationURI = query.value(1).toUrl();
            QUrl arrivalStationURI = query.value(2).toUrl();
            QDateTime departureTime = query.value(3).toDateTime();
            QDateTime arrivalTime = query.value(4).toDateTime();
            qint16 departureDelay = query.value(5).toInt();
            qint16 arrivalDelay = query.value(6).toInt();
            QUrl tripURI = query.value(7).toUrl();
            QUrl routeURI = query.value(8).toUrl();
            QString direction = query.value(9).toString();

            // Generate LinkedConnectionFragment and return it
            LinkedConnectionFragment *fragment = new LinkedConnectionFragment(uri,
                                                                              departureStationURI,
                                                                              arrivalStationURI,
                                                                              departureTime,
                                                                              arrivalTime,
                                                                              departureDelay,
                                                                              arrivalDelay,
                                                                              tripURI,
                                                                              routeURI,
                                                                              direction,
                                                                              m_instance);
            return fragment;
        }
    }

    qDebug() << "Non-valid Linked Connections fragments found, number of records:" << query.size();
    return nullptr;
}

void LinkedConnectionsFactory::getFragmentFromHTTPManager(const QUrl &uri)
{
    this->http()->getResource(uri);
    // attach signal handler
}

void LinkedConnectionsFactory::initDatabase()
{
    // On instantation, create the fragments table in the database if it doesn't exist yet.
    QSqlQuery query(this->db()->database());
    bool succes = query.prepare("CREATE TABLE IF NOT EXISTS fragments ("
                                "uri TEXT PRIMARY KEY, "
                                "departureStationURI TEXT, "
                                "arrivalStationURI TEXT, "
                                "departureTime TEXT, "
                                "arrivalTime TEXT, "
                                "departureDelay INT, "
                                "arrivalDELAY INT, "
                                "tripURI TEXT, "
                                "routeURI TEXT, "
                                "direction TEXT)");
    if(!succes)
    {
        qCritical() << "Unable to create 'fragments' table:" << query.lastError().text();
    }
    this->db()->execute(query);
}

DatabaseManager *LinkedConnectionsFactory::db() const
{
    return m_db;
}

void LinkedConnectionsFactory::setDb(DatabaseManager *db)
{
    m_db = db;
}

HTTPManager *LinkedConnectionsFactory::http() const
{
    return m_http;
}

void LinkedConnectionsFactory::setHttp(HTTPManager *http)
{
    m_http = http;
}

