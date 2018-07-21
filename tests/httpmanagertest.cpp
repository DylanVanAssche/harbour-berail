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

#include "httpmanagertest.h"

/**
 * @file httpmanagertest.cpp
 * @author Dylan Van Assche
 * @date 17 Jul 2018
 * @brief HTTPManagerTest init
 * Init HTTPManagerTest
 */
void HTTPManagerTest::initHTTPManager() {
    qDebug() << "Init HTTP";
    http = new HTTPManager();
    connect(http, SIGNAL(requestCompleted(QNetworkReply*)), this, SLOT(processReply(QNetworkReply*)));
}

/**
 * @file httpmanagertest.cpp
 * @author Dylan Van Assche
 * @date 17 Jul 2018
 * @brief HTTPManagerTest run tests
 * Run HTTPManager tests:
 *  - GET request
 *  - POST request
 *  - DELETE request
 *  - HEAD request
 */
void HTTPManagerTest::runHTTPManager()
{
    // Activate QSignalSpy
    QSignalSpy spy(http, SIGNAL(onRequestCompleted(QNetworkReply *)));

    // HTTP GET
    http->getResource(QUrl("https://httpbin.org/get"));
    // Wait for signal
    QVERIFY(spy.wait(2000));

    // HTTP POST
    http->postResource(QUrl("https://httpbin.org/post"), QByteArray("HTTP POST OK"));
    // Wait for signal
    QVERIFY(spy.wait(2000));

    // HTTP DELETE
    http->deleteResource(QUrl("https://httpbin.org/delete"));
    // Wait for signal
    QVERIFY(spy.wait(2000));

    // HTTP POST
    http->headResource(QUrl("https://httpbin.org/get"));
    // Wait for signal
    QVERIFY(spy.wait(2000));
}

/**
 * @file httpmanagertest.cpp
 * @author Dylan Van Assche
 * @date 17 Jul 2018
 * @brief HTTPManagerTest clean up
 * Init HTTPManagerTest
 */
void HTTPManagerTest::cleanHTTPManager()
{
    qDebug() << "Cleaning up HTTP";
    http->deleteLater();
}

/**
 * @file httpmanagertest.cpp
 * @author Dylan Van Assche
 * @date 17 Jul 2018
 * @brief HTTPManagerTest reply handler
 * Handles the HTTP replies from the HTTPManager by checking the HTTP status code and log it.
 */
void HTTPManagerTest::processReply(QNetworkReply *reply)
{
    QCOMPARE(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(), 200); // HTTP 200 OK check
    qDebug() << reply->readAll();
}
