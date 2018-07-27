#ifndef LINKEDCONNECTIONSFACTORYTEST_H
#define LINKEDCONNECTIONSFACTORYTEST_H

#include <QObject>
#include <QtTest/QtTest>
#include <QSignalSpy>
#include <QtSql/QSqlQuery>
#include "../src/linkedconnections/linkedconnectionsfactory.h"
#include "../src/database/databasemanager.h"

class LinkedConnectionsFactoryTest : public QObject
{
    Q_OBJECT
private slots:
    void initLinkedConnectionsFactory();
    void runLinkedConnectionsFactory();
    void cleanLinkedConnectionsFactory();

private:
    LinkedConnectionsFactory *factory;
    DatabaseManager *db;
};

#endif // LINKEDCONNECTIONSFACTORYTEST_H
