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
#define BASE_URL "https://graph.irail.be/sncb/connections"

// Factory pattern to generate Linked Connections fragments on the fly
class LinkedConnectionsFactory: public QObject
{
    Q_OBJECT
public:
    static LinkedConnectionsFactory *getInstance(const QString &path, QObject *parent = nullptr);
    void getPage(const QUrl &uri);
    void getPage(const QDateTime &timestamp);

signals:
    void pageReady(LinkedConnectionPage *page);

private slots:
    void processHTTPReply(QNetworkReply *reply);

private:
    static LinkedConnectionsFactory *m_instance;
    HTTPManager *m_http;
    void getPageByURIFromHTTPManager(const QUrl &uri);
    LinkedConnectionFragment *generateFragmentFromJSON(const QJsonObject &connection);
    explicit LinkedConnectionsFactory(const QString &path, QObject *parent);
    HTTPManager *http() const;
    void setHttp(HTTPManager *http);
};

#endif // LINKEDCONNECTIONSFACTORY_H
