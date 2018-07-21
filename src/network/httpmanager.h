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

#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H

#include <QObject>
#include <QtCore/QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkConfigurationManager>

class HTTPManager : public QObject
{
    Q_OBJECT
public:
    explicit HTTPManager(QObject *parent = nullptr);
    QString userAgent() const;
    void setUserAgent(const QString &userAgent);
    QString acceptHeader() const;
    void setAcceptHeader(const QString &acceptHeader);
    void getResource(const QUrl &url, const QUrlQuery &parameters = nullptr);
    void postResource(const QUrl &url, const QByteArray &data);
    void deleteResource(const QUrl &url);
    void headResource(const QUrl &url);

signals:
    void requestCompleted(QNetworkReply *reply);
    QList<QSslError> sslErrorsReceived(QNetworkReply* reply, QList<QSslError> sslError);
    QNetworkAccessManager::NetworkAccessibility networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility state);
    void userAgentChanged();
    void acceptHeaderChanged();

private:
    QNetworkRequest prepareRequest(const QUrl &url);
    QNetworkAccessManager *QNAM;
    QString m_userAgent;
    QString m_acceptHeader;
};

#endif // HTTPMANAGER_H
