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

#include "http.h"

/**
 * @file http.cpp
 * @author Dylan Van Assche
 * @date 17 Jul 2018
 * @brief HTTP facade constructor
 * Constructs a HTTP facade to access the network using the HTTP protocol.
 * The HTTP facade makes network access in Qt abstract from the underlying library (QNetworkAccessManager, libCurl, ...).
 */
HTTP::HTTP(QObject *parent) : QObject(parent)
{
    // Initiate a new QNetworkAccessManager with cache
    QNAM = new QNetworkAccessManager(this);
    QNetworkConfigurationManager QNAMConfig;
    QNAM->setConfiguration(QNAMConfig.defaultConfiguration());

    // Connect QNetworkAccessManager signals
    connect(QNAM, SIGNAL(networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility)), this, SLOT(onNetworkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility)));
    connect(QNAM, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)), this, SLOT(onSSLErrorsReceived(QNetworkReply*,QList<QSslError>)));
    connect(QNAM, SIGNAL(finished(QNetworkReply*)), this, SIGNAL(onRequestCompleted(QNetworkReply*)));

    // Create HTTP client information
    this->setUserAgent(QString("%1/%2 (%3)").arg("BeRail-LC", "V0.0.1", "2.2.0.29"));
    this->setAcceptHeader(QString("application/ld+json"));
}

// Invokers
/**
 * @file http.cpp
 * @author Dylan Van Assche
 * @date 17 Jul 2018
 * @brief Get a resource
 * @param QUrl url
 *
 * Retrieves a certain resource from the given QUrl url.
 * The result as a QNetworkReply *reply will be available as soon as the onRequestCompleted signal is fired.
 */
void HTTP::getResource(const QUrl &url)
{
    qDebug() << "GET resource";
    QNetworkRequest request = this->prepareRequest(url);
    QNAM->get(request);
}

/**
 * @file http.cpp
 * @author Dylan Van Assche
 * @date 17 Jul 2018
 * @brief Post to a resource
 * @param const QUrl &url
 *
 * Posts data to a certain resource from the given QUrl url.
 * The result as a QNetworkReply *reply will be available as soon as the onRequestCompleted signal is fired.
 */
void HTTP::postResource(const QUrl &url, const QByteArray &data)
{
    qDebug() << "POST resource";
    QNetworkRequest request = this->prepareRequest(url);
    QNAM->post(request, data);
}

/**
 * @file http.cpp
 * @author Dylan Van Assche
 * @date 17 Jul 2018
 * @brief Delete a resource
 * @param const QUrl &url
 *
 * Deletes a certain resource from the given QUrl url.
 * The result as a QNetworkReply *reply will be available as soon as the onRequestCompleted signal is fired.
 */
void HTTP::deleteResource(const QUrl &url)
{
    qDebug() << "DELETE resource";
    QNetworkRequest request = this->prepareRequest(url);
    QNAM->deleteResource(request);
}

// Helpers
/**
 * @file http.cpp
 * @author Dylan Van Assche
 * @date 17 Jul 2018
 * @brief Prepare the HTTP request
 * @param const QUrl &url
 * @return QNetworkRequest request
 *
 * Everytime a HTTP request has been made by the user it needs several default headers to complete it's mission.
 * The prepareRequest method just does that, it adds the Accept, User-Agent header to the request and allows redirects.
 */
QNetworkRequest HTTP::prepareRequest(const QUrl &url)
{
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, this->acceptHeader());
    request.setHeader(QNetworkRequest::UserAgentHeader, this->userAgent());
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    return request;
}

// Handlers
/**
 * @file http.cpp
 * @author Dylan Van Assche
 * @date 17 Jul 2018
 * @brief Network accessible signal
 * @param QNetworkAccessManager::NetworkAccessibility state
 * @return QNetworkAccessManager::NetworkAccessibility state
 *
 * The user can listen to the signal to react on network state changes.
 * The QNetworkAccessManager::NetworkAccessibility enum contains all the possible network states.
 * @see https://doc.qt.io/qt-5.6/qnetworkaccessmanager.html#NetworkAccessibility-enum
 */
QNetworkAccessManager::NetworkAccessibility HTTP::onNetworkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility state)
{
    qDebug() << "Network accessiblity state changed:" << state;
    return state;
}

/**
 * @file http.cpp
 * @author Dylan Van Assche
 * @date 17 Jul 2018
 * @brief SSL errors received signal
 * @param QList<QSslError> sslError
 * @return QList<QSslError> sslError
 *
 * The user can listen to the signal to react on SSL errors.
 */
QList<QSslError> HTTP::onSSLErrorsReceived(QNetworkReply *reply, QList<QSslError> sslError)
{
    qCritical() << "SSL Error!" << sslError;
    return sslError;
}

// Getter & Setters
/**
 * @file http.cpp
 * @author Dylan Van Assche
 * @date 17 Jul 2018
 * @brief Gets the current user agent
 * @return QString userAgent
 *
 * Retrieves the current user agent used to make requests in this HTTP instance.
 */
QString HTTP::userAgent() const
{
    return m_userAgent;
}

/**
 * @file http.cpp
 * @author Dylan Van Assche
 * @date 17 Jul 2018
 * @brief Sets the current user agent
 * @param const QString &userAgent
 *
 * Changes the current user agent to the given QString.
 */
void HTTP::setUserAgent(const QString &userAgent)
{
    m_userAgent = userAgent;
}

/**
 * @file http.cpp
 * @author Dylan Van Assche
 * @date 17 Jul 2018
 * @brief Get the current accept header
 * @return QString acceptHeader
 *
 * Retrieves the current accept header used to make requests in this HTTP instance.
 */
QString HTTP::acceptHeader() const
{
    return m_acceptHeader;
}

/**
 * @file http.cpp
 * @author Dylan Van Assche
 * @date 17 Jul 2018
 * @brief Sets the current accept header
 * @param const QString &acceptHeader
 *
 * Changes the current accept header to the given QString.
 */
void HTTP::setAcceptHeader(const QString &acceptHeader)
{
    m_acceptHeader = acceptHeader;
}
