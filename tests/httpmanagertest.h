#ifndef HTTPMANAGERTEST_H
#define HTTPMANAGERTEST_H

#include <QObject>
#include <QtTest/QtTest>
#include <QSignalSpy>
#include "../src/network/httpmanager.h"

class HTTPManagerTest : public QObject
{
    Q_OBJECT
private slots:
    void initHTTPManager();
    void runHTTPManager();
    void cleanHTTPManager();

public slots:
    void processReply(QNetworkReply *reply);

private:
    HTTPManager *http;
};

#endif // HTTPMANAGERTEST_H
