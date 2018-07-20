#include "httptest.h"

void HTTPTest::initHTTPManager() {
    qDebug() << "Init HTTP";
    http = new HTTPManager();
    connect(http, SIGNAL(onRequestCompleted(QNetworkReply*)), this, SLOT(processReply(QNetworkReply*)));
}

void HTTPTest::runHTTPManagerTest()
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
}

void HTTPTest::cleanHTTPManager()
{
    qDebug() << "Cleaning up HTTP";
    http->deleteLater();
}

void HTTPTest::processReply(QNetworkReply *reply)
{
    QCOMPARE(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(), 200); // HTTP 200 OK check
    qDebug() << reply->readAll();
}

