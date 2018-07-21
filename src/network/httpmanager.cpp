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

#include "httpmanager.h"

/**
 * @file httpmanager.cpp
 * @author Dylan Van Assche
 * @date 17 Jul 2018
 * @brief HTTPManager facade constructor
 * @public
 * Constructs a HTTPManager facade to access the network using the HTTP protocol.
 * The HTTPManager facade makes network access in Qt abstract from the underlying library (QNetworkAccessManager, libCurl, ...).
 */
HTTPManager::HTTPManager(QObject* parent): QObject(parent)
{
    // Set parent of this QObject. When parent is destroyed, this one is automatically cleaned up too.
    this->setParent(parent);

    // Initiate a new QNetworkAccessManager with cache
    QNAM = new QNetworkAccessManager(this);
    QNetworkConfigurationManager QNAMConfig;
    QNAM->setConfiguration(QNAMConfig.defaultConfiguration());

    // Connect QNetworkAccessManager signals
    connect(QNAM, SIGNAL(networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility)), this, SIGNAL(networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility)));
    connect(QNAM, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)), this, SIGNAL(sslErrorsReceived(QNetworkReply*,QList<QSslError>)));
    connect(QNAM, SIGNAL(finished(QNetworkReply*)), this, SIGNAL(requestCompleted(QNetworkReply*)));

    // Create HTTP client information
    this->setUserAgent(QString("%1/%2 (%3)").arg("BeRail-LC", "V0.0.1", "2.2.0.29"));
    this->setAcceptHeader(QString("application/ld+json"));
}

// Invokers
/**
 * @file httpmanager.cpp
 * @author Dylan Van Assche
 * @date 17 Jul 2018
 * @brief Get a resource
 * @param const QUrl &url
 * @param const QUrlQuery &parameters = nullptr
 * @public
 * Retrieves a certain resource from the given QUrl url using a GET request.
 * The result as a QNetworkReply *reply will be available as soon as the requestCompleted signal is fired.
 */
void HTTPManager::getResource(const QUrl &url, const QUrlQuery &parameters = nullptr)
{
    qDebug() << "GET resource:" << url;
    if(parameters != nullptr) {
        qDebug() << "Processing GET parameters";
        url.setQuery(parameters);
    }
    QNetworkRequest request = this->prepareRequest(url);
    QNAM->get(request);
}

/**
 * @file httpmanager.cpp
 * @author Dylan Van Assche
 * @date 17 Jul 2018
 * @brief Post to a resource
 * @param const QUrl &url
 * @public
 * Posts data to a certain resource from the given QUrl url using a POST request.
 * The result as a QNetworkReply *reply will be available as soon as the requestCompleted signal is fired.
 */
void HTTPManager::postResource(const QUrl &url, const QByteArray &data)
{
    qDebug() << "POST resource:" << url;
    QNetworkRequest request = this->prepareRequest(url);
    QNAM->post(request, data);
}

/**
 * @file httpmanager.cpp
 * @author Dylan Van Assche
 * @date 17 Jul 2018
 * @brief Delete a resource
 * @param const QUrl &url
 * @public
 * Deletes a certain resource from the given QUrl url using a DELETE request.
 * The result as a QNetworkReply *reply will be available as soon as the requestCompleted signal is fired.
 */
void HTTPManager::deleteResource(const QUrl &url)
{
    qDebug() << "DELETE resource:" << url;
    QNetworkRequest request = this->prepareRequest(url);
    QNAM->deleteResource(request);
}

/**
 * @file httpmanager.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Head a resource
 * @param const QUrl &url
 * @public
 * Retrieves the headers of the resource from the given QUrl url using a HEAD request.
 * The result as a QNetworkReply *reply will be available as soon as the requestCompleted signal is fired.
 */
void HTTPManager::headResource(const QUrl &url)
{
    qDebug() << "HEAD resource:" << url;
    QNetworkRequest request = this->prepareRequest(url);
    QNAM->head(request);
}

// Helpers
/**
 * @file httpmanager.cpp
 * @author Dylan Van Assche
 * @date 17 Jul 2018
 * @brief Prepare the HTTP request
 * @param const QUrl &url
 * @return QNetworkRequest request
 * @public
 * Everytime a HTTP request has been made by the user it needs several default headers to complete it's mission.
 * The prepareRequest method just does that, it adds the Accept, User-Agent header to the request and allows redirects.
 */
QNetworkRequest HTTPManager::prepareRequest(const QUrl &url)
{
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, this->acceptHeader());
    request.setHeader(QNetworkRequest::UserAgentHeader, this->userAgent());
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    return request;
}

// Getter & Setters
/**
 * @file httpmanager.cpp
 * @author Dylan Van Assche
 * @date 17 Jul 2018
 * @brief Gets the current user agent
 * @return QString userAgent
 * @public
 * Retrieves the current user agent used to make requests in this HTTP instance.
 */
QString HTTPManager::userAgent() const
{
    return m_userAgent;
}

/**
 * @file httpmanager.cpp
 * @author Dylan Van Assche
 * @date 17 Jul 2018
 * @brief Sets the current user agent
 * @param const QString &userAgent
 * @public
 * Changes the current user agent to the given QString.
 */
void HTTPManager::setUserAgent(const QString &userAgent)
{
    m_userAgent = userAgent;
}

/**
 * @file httpmanager.cpp
 * @author Dylan Van Assche
 * @date 17 Jul 2018
 * @brief Get the current accept header
 * @return QString acceptHeader
 * @public
 * Retrieves the current accept header used to make requests in this HTTP instance.
 */
QString HTTPManager::acceptHeader() const
{
    return m_acceptHeader;
}

/**
 * @file httpmanager.cpp
 * @author Dylan Van Assche
 * @date 17 Jul 2018
 * @brief Sets the current accept header
 * @param const QString &acceptHeader
 * @public
 * Changes the current accept header to the given QString.
 */
void HTTPManager::setAcceptHeader(const QString &acceptHeader)
{
    m_acceptHeader = acceptHeader;
}
