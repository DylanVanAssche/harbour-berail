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

// Singleton pattern

LinkedConnectionsFactory::LinkedConnectionsFactory(const QString &path, QObject *parent): QObject(parent)
{
    // Set parent of this QObject. When parent is destroyed, this one is automatically cleaned up too.
    this->setParent(parent);
    this->setHttp(HTTPManager::getInstance(parent));
    connect(this->http(), SIGNAL(requestCompleted(QNetworkReply *)), this, SLOT(processHTTPReply(QNetworkReply *)));
}

LinkedConnectionsFactory *LinkedConnectionsFactory::getInstance(const QString &path, QObject *parent)
{
    // Singleton pattern
    if(m_instance == nullptr) {
        qDebug() << "Generating new LinkedConnectionsFactory";
        m_instance = new LinkedConnectionsFactory(path, parent);
    }
    return m_instance;
}

// Invokers
void LinkedConnectionsFactory::getPage(const QUrl &uri)
{
    // Use processing methods to allow other extensions in the future if needed
    this->getPageByURIFromHTTPManager(uri);
}

void LinkedConnectionsFactory::getPage(const QDateTime &timestamp)
{
    // Construct the URI of the page
    QUrl uri = QUrl(BASE_URL);
    QUrlQuery parameters;
    // Qt:ISODate returns 2018-07-27T14:18:40 while we need 2018-07-27T14:18:40.000Z
    parameters.addQueryItem("departureTime", timestamp.toString(Qt::ISODate) + ".000Z");
    uri.setQuery(parameters);

    // Use processing methods to allow other extensions in the future if needed
    this->getPageByURIFromHTTPManager(uri);
}

// Processors
void LinkedConnectionsFactory::getPageByURIFromHTTPManager(const QUrl &uri)
{
    this->http()->getResource(uri);
}

// Helpers
LinkedConnectionFragment *LinkedConnectionsFactory::generateFragmentFromJSON(const QJsonObject &connection)
{
    QUrl uri = QUrl(connection["@id"].toString());
    QUrl departureStationURI = QUrl(connection["departureStop"].toString());
    QUrl arrivalStationURI = QUrl(connection["arrivalStop"].toString());
    QDateTime departureTime = QDateTime::fromString(connection["departureTime"].toString(), Qt::ISODate);
    QDateTime arrivalTime = QDateTime::fromString(connection["arrivalTime"].toString(), Qt::ISODate);
    QUrl tripURI = QUrl(connection["gtfs:trip"].toString());
    QUrl routeURI = QUrl(connection["gtfs:route"].toString());
    qint16 departureDelay;
    qint16 arrivalDelay;
    if(connection.contains("departureDelay")) {
        departureDelay = connection["departureDelay"].toInt();
    }
    if(connection.contains("arrivalDelay")) {
        arrivalDelay = connection["arrivalDelay"].toInt();
    }
    QString direction = connection["direction"].toString();
    qDebug() << "Fragment retrieved:" << uri;

    LinkedConnectionFragment *frag = new LinkedConnectionFragment(
                uri,
                departureStationURI,
                arrivalStationURI,
                departureTime,
                arrivalTime,
                departureDelay,
                arrivalDelay,
                tripURI,
                routeURI,
                direction,
                m_instance
                );
    return frag;
}

void LinkedConnectionsFactory::processHTTPReply(QNetworkReply *reply)
{
    if(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200) {
        qDebug() << "Content-Header:" << reply->header(QNetworkRequest::ContentTypeHeader).toString();
        qDebug() << "Content-Length:" << reply->header(QNetworkRequest::ContentLengthHeader).toULongLong() << "bytes";
        qDebug() << "HTTP code:" << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug() << "HTTP reason:" << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
        qDebug() << "Cache:" << reply->attribute(QNetworkRequest::SourceIsFromCacheAttribute).toBool();

        // Read HTTP reply
        QString replyData = (QString)reply->readAll();

        // HTTP 200 OK, create LCPage and LCFragment list
        QList<LinkedConnectionFragment *> fragments = QList<LinkedConnectionFragment *>();

        // Try to parse the data as JSON
        QJsonParseError parseError;
        QJsonDocument jsonData = QJsonDocument::fromJson(replyData.toUtf8(), &parseError);
        if(parseError.error == QJsonParseError::NoError) {
            QJsonObject jsonObject = jsonData.object();

            // Linked Connections fragments
            QJsonArray graph = jsonObject["@graph"].toArray();

            foreach(QJsonValue item, graph) {
                QJsonObject connection = item.toObject();
                LinkedConnectionFragment *frag = this->generateFragmentFromJSON(connection);
                fragments.append(frag);
            }

            // Linked Connections page
            QString pageURI = jsonObject["@id"].toString();
            QDateTime pageTimestamp = QDateTime::fromString(pageURI.right(24), Qt::ISODate); // TO DO REGEX
            QString hydraNext = jsonObject["hydra:next"].toString();
            QString hydraPrevious = jsonObject["hydra:previous"].toString();
            LinkedConnectionPage *page = new LinkedConnectionPage(
                        pageURI,
                        pageTimestamp,
                        hydraNext,
                        hydraPrevious,
                        fragments
                        );

            emit this->pageReady(page);
        }
        else {
            qWarning() << "Parsing JSON data failed:" << parseError.errorString();
        }

    }
    else {
        qWarning() << reply->readAll();
        qWarning() << "HTTP request failed! HTTP code:" << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString();
    }
    reply->deleteLater();
}

// Getters & Setters
HTTPManager *LinkedConnectionsFactory::http() const
{
    return m_http;
}

void LinkedConnectionsFactory::setHttp(HTTPManager *http)
{
    m_http = http;
}

