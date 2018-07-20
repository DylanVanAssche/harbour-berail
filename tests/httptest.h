#ifndef HTTPTEST_H
#define HTTPTEST_H

#include <QObject>
#include <QtTest/QtTest>
#include <QSignalSpy>
#include "../src/network/httpmanager.h"

class HTTPTest : public QObject
{
    Q_OBJECT

private slots:
    void initHTTPManager();
    void runHTTPManagerTest();
    void cleanHTTPManager();

public slots:
    void processReply(QNetworkReply *reply);

private:
    HTTPManager *http;
};

#endif // HTTPTEST_H
