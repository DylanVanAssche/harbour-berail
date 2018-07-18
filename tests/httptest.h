#ifndef HTTPTEST_H
#define HTTPTEST_H

#include <QObject>
#include <QtTest/QtTest>
#include <QSignalSpy>
#include "../src/network/http.h"

class HTTPTest : public QObject
{
    Q_OBJECT

private slots:
    void initHTTP();
    void getRequest();
    void cleanHTTP();

public slots:
    void processReply(QNetworkReply *reply);

private:
    HTTP *http;
};

#endif // HTTPTEST_H
