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
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonParseError>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include "linkedconnectionfragment.h"
#include "linkedconnectionpage.h"
#include "../network/httpmanager.h"
#include "../database/databasemanager.h"
#define BASE_URL "https://graph.irail.be/sncb/connections?departureTime="

// Factory pattern to generate Linked Connections fragments on the fly
class LinkedConnectionsFactory: public QObject
{
    Q_OBJECT
public:
    static LinkedConnectionsFactory *getInstance(const QString &path, QObject *parent = nullptr);
    void getPage(const QUrl &uri);

signals:
    void fragmentsReady(const QList<LinkedConnectionFragment *> &fragments);
    void pageReady(const LinkedConnectionPage *page);

private slots:
    void processHTTPReply(QNetworkReply *reply);

private:
    static LinkedConnectionsFactory *m_instance;
    HTTPManager *m_http;
    DatabaseManager *m_db;
    QList<LinkedConnectionFragment *> getPageByURIFromDatabaseManager(const QUrl &uri);
    void getPageByURIFromHTTPManager(const QUrl &uri);
    void initDatabase();
    bool isPageInDatabase(const QUrl &uri);
    bool addPageToDatabase(const QString &uri, const qint64 &timestamp, const QString &hydraNext, const QString &hydraPrevious);
    bool addFragmentToDatabase(const QString &pageURI, LinkedConnectionFragment *fragment);
    LinkedConnectionFragment *generateFragmentFromJSON(const QJsonObject &connection);
    explicit LinkedConnectionsFactory(const QString &path, QObject *parent);
    HTTPManager *http() const;
    void setHttp(HTTPManager *http);
    DatabaseManager *db() const;
    void setDb(DatabaseManager *db);
};

#endif // LINKEDCONNECTIONSFACTORY_H
