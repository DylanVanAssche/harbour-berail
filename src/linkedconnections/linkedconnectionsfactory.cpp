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
    this->setDb(DatabaseManager::getInstance(path, parent));
    this->setHttp(HTTPManager::getInstance(parent));
    this->initDatabase();
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
    // Try to fetch the page from the database
    QList<LinkedConnectionFragment *> fragments = this->getPageByURIFromDatabaseManager(uri);

    // If list is empty then the page isn't cached yet
    if(fragments.size() == 0) {
        qDebug() << "Database can't find page, fetching now...";
        this->getPageByURIFromHTTPManager(uri);
    }
    else {
        qDebug() << "Emitting fragmentsReady signal since page cached by DB";
        emit fragmentsReady(fragments);
    }
}

// Processors
QList<LinkedConnectionFragment *> LinkedConnectionsFactory::getPageByURIFromDatabaseManager(const QUrl &uri)
{
    QSqlQuery query(this->db()->database());
    QList<LinkedConnectionFragment *> fragments;
    qDebug() << "Is PAGE IN DB>" << this->isPageInDatabase(uri);
    if(this->isPageInDatabase(uri)) {
        // Finding fragments from the page
        query.prepare("SELECT "
                      "uri,"
                      "page,"
                      "departureStationURI,"
                      "arrivalStationURI,"
                      "departureTime,"
                      "arrivalTime,"
                      "departureDelay,"
                      "arrivalDelay,"
                      "tripURI,"
                      "routeURI,"
                      "direction"
                      " FROM fragments WHERE page = ? "
                      "ORDER BY departureTime DESC"); // Sorting the results (descending order) for the CSA algorithm
        query.addBindValue(uri); // Match page URI's
        this->db()->execute(query);
        while (query.next())
        {
            // Using the field name in overload query.value(x) is less efficient then using indexes according to the Qt 5.6.3 docs
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

            // Generate a new LinkedConnectionFragment and append it
            LinkedConnectionFragment *frag = new LinkedConnectionFragment(uri,
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
            fragments.append(frag);
        }
    }
    return fragments;
}

void LinkedConnectionsFactory::getPageByURIFromHTTPManager(const QUrl &uri)
{
    this->http()->getResource(uri);
}

// Helpers
void LinkedConnectionsFactory::initDatabase()
{
    // On instantation, create the fragments table in the database if it doesn't exist yet.
    QSqlQuery query(this->db()->database());

    // PAGES table
    bool succes = query.prepare("CREATE TABLE IF NOT EXISTS pages ("
                                "uri TEXT PRIMARY KEY, "
                                "timestamp INT, " // Sorting using UNIX timestamp is much faster then DATE based according to the SQLite docs.
                                "hydraNext TEXT, "
                                "hydraPrevious TEXT)");
    succes = this->db()->execute(query);
    query.clear(); // Release resources for reuse

    // FRAGMENTS table
    succes = query.prepare("CREATE TABLE IF NOT EXISTS fragments ("
                           "uri TEXT PRIMARY KEY, "
                           "page TEXT, "
                           "departureStationURI TEXT, "
                           "arrivalStationURI TEXT, "
                           "departureTime TEXT, "
                           "arrivalTime TEXT, "
                           "departureDelay INT, "
                           "arrivalDELAY INT, "
                           "tripURI TEXT, "
                           "routeURI TEXT, "
                           "direction TEXT)");
    succes = this->db()->execute(query);

    if(succes)
    {
        qDebug() << "Database init OK";
    }
    else {
        qCritical() << "Unable to create tables:" << query.lastError().text();
    }
}

bool LinkedConnectionsFactory::isPageInDatabase(const QUrl &uri)
{
    QSqlQuery query(this->db()->database());
    // Qt 5.6.3 docs: Using SELECT * is not recommended because the order of the fields in the query is undefined.
    // Find page by URI
    query.prepare("SELECT uri FROM pages WHERE uri = ?");
    query.addBindValue(uri.toString()); // Match URI's
    this->db()->execute(query);
    return query.next(); // Page in database when #records != 0
}

bool LinkedConnectionsFactory::addPageToDatabase(const QString &uri, const qint64 &timestamp, const QString &hydraNext, const QString &hydraPrevious)
{
    QSqlQuery query(this->db()->database());
    query.prepare("INSERT INTO "
                  "pages(uri, timestamp, hydraNext, hydraPrevious) "
                  "VALUES(:uri, :timestamp, :hydraNext, :hydraPrevious)");
    query.bindValue(":uri", uri);
    query.bindValue(":timestamp", timestamp);
    query.bindValue(":hydraNext", hydraNext);
    query.bindValue(":hydraPrevious", hydraPrevious);
    return this->db()->execute(query);
}

bool LinkedConnectionsFactory::addFragmentToDatabase(const QString &pageURI, LinkedConnectionFragment *fragment)
{
    QSqlQuery query(this->db()->database());
    query.prepare("INSERT INTO fragments ("
                  "uri, "
                  "page, "
                  "departureStationURI, "
                  "arrivalStationURI, "
                  "departureTime, "
                  "arrivalTime, "
                  "departureDelay, "
                  "arrivalDelay, "
                  "tripURI, "
                  "routeURI, "
                  "direction)"
                  " VALUES(:uri, "
                  ":page, "
                  ":departureStationURI, "
                  ":arrivalStationURI, "
                  ":departureTime, "
                  ":arrivalTime, "
                  ":departureDelay, "
                  ":arrivalDelay, "
                  ":tripURI, "
                  ":routeURI, "
                  ":direction)");
    query.bindValue(":uri", fragment->uri().toString());
    query.bindValue(":page", pageURI);
    query.bindValue(":departureStationURI", fragment->departureStationURI().toString());
    query.bindValue(":arrivalStationURI", fragment->arrivalStationURI().toString());
    query.bindValue(":departureTime", fragment->departureTime().toMSecsSinceEpoch());
    query.bindValue(":arrivalTime", fragment->arrivalTime().toMSecsSinceEpoch());
    query.bindValue(":departureDelay", fragment->departureDelay());
    query.bindValue(":arrivalDelay", fragment->arrivalDelay());
    query.bindValue(":tripURI", fragment->tripURI().toString());
    query.bindValue(":routeURI", fragment->routeURI().toString());
    query.bindValue(":direction", fragment->direction());
    return this->db()->execute(query);
}

LinkedConnectionFragment *LinkedConnectionsFactory::generateLCFragmentFromJSON(const QJsonObject &connection)
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
    QList<LinkedConnectionFragment *> fragments = QList<LinkedConnectionFragment *>();

    if(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200) {
        qDebug() << "Content-Header:" << reply->header(QNetworkRequest::ContentTypeHeader).toString();
        qDebug() << "Content-Length:" << reply->header(QNetworkRequest::ContentLengthHeader).toULongLong() << "bytes";
        qDebug() << "HTTP code:" << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug() << "HTTP reason:" << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
        qDebug() << "Cache:" << reply->attribute(QNetworkRequest::SourceIsFromCacheAttribute).toBool();

        // Check if the redirect URL is already in our database
        fragments = this->getPageByURIFromDatabaseManager(reply->url());

        if(reply->operation() == QNetworkAccessManager::Operation::HeadOperation) {
            if(fragments.size() == 0) {
                qDebug() << "Page is out of date or not in database, fetching now...";
                // Handle HEAD request for caching purposes TODO
            }
        }
        else if(reply->operation() == QNetworkAccessManager::Operation::GetOperation) {
            // Redirect URL isn't in DB, process the dataset
            if(fragments.size() == 0) {
                // Get the data from the request
                QString replyData = (QString)reply->readAll();

                // Prepare database queries in a transaction for performance reasons
                this->db()->startTransaction();

                // Try to parse the data as JSON
                QJsonParseError parseError;
                QJsonDocument jsonData = QJsonDocument::fromJson(replyData.toUtf8(), &parseError);
                if(parseError.error == QJsonParseError::NoError) {
                    QJsonObject jsonObject = jsonData.object();
                    // Linked Connections page
                    // Save page in DB
                    QString pageURI = jsonObject["@id"].toString();
                    qint64 pageTimestamp = (QDateTime::fromString(pageURI.right(24), Qt::ISODate)).toMSecsSinceEpoch(); // TODO regex
                    QString hydraNext = jsonObject["hydra:next"].toString();
                    QString hydraPrevious = jsonObject["hydra:previous"].toString();
                    this->addPageToDatabase(pageURI, pageTimestamp, hydraNext, hydraPrevious);

                    // Linked Connections fragments
                    QJsonArray graph = jsonObject["@graph"].toArray();

                    foreach(QJsonValue item, graph) {
                        QJsonObject connection = item.toObject();
                        LinkedConnectionFragment *frag = this->generateLCFragmentFromJSON(connection);
                        this->addFragmentToDatabase(pageURI, frag);
                        fragments.append(frag);
                    }
                }
                else {
                    qWarning() << "Parsing JSON data failed:" << parseError.errorString();
                }

                // Finish insertion and clean up
                this->db()->endTransaction();
                qDebug() << fragments.size() << "fragments ready in DB";
            }
        }
        reply->deleteLater();
    }
    else {
        qWarning() << reply->readAll();
        qWarning() << "HTTP request failed! HTTP code:" << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString();
    }

    // Emit in all cases to avoid blocking callback
    emit this->fragmentsReady(fragments);
}

// Getters & Setters
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

