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
HTTPManager::HTTPManager()
{
    // Initiate a new QNetworkAccessManager with cache
    QNAM = new QNetworkAccessManager(this);
    QNetworkConfigurationManager QNAMConfig;
    QNAM->setConfiguration(QNAMConfig.defaultConfiguration());

    // Connect QNetworkAccessManager signals
    connect(QNAM, SIGNAL(networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility)), this, SIGNAL(onNetworkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility)));
    connect(QNAM, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)), this, SIGNAL(onSSLErrorsReceived(QNetworkReply*,QList<QSslError>)));
    connect(QNAM, SIGNAL(finished(QNetworkReply*)), this, SIGNAL(onRequestCompleted(QNetworkReply*)));

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
 * @param QUrl url
 * @public
 * Retrieves a certain resource from the given QUrl url.
 * The result as a QNetworkReply *reply will be available as soon as the onRequestCompleted signal is fired.
 */
void HTTPManager::getResource(const QUrl &url)
{
    qDebug() << "GET resource";
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
 * Posts data to a certain resource from the given QUrl url.
 * The result as a QNetworkReply *reply will be available as soon as the onRequestCompleted signal is fired.
 */
void HTTPManager::postResource(const QUrl &url, const QByteArray &data)
{
    qDebug() << "POST resource";
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
 * Deletes a certain resource from the given QUrl url.
 * The result as a QNetworkReply *reply will be available as soon as the onRequestCompleted signal is fired.
 */
void HTTPManager::deleteResource(const QUrl &url)
{
    qDebug() << "DELETE resource";
    QNetworkRequest request = this->prepareRequest(url);
    QNAM->deleteResource(request);
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
