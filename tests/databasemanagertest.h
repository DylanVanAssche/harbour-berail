#ifndef DATABASEMANAGERTEST_H
#define DATABASEMANAGERTEST_H

#include <QObject>
#include <QtTest/QtTest>
#include <QSignalSpy>
#include <QSqlQuery>
#include "../src/database/databasemanager.h"

class DatabaseManagerTest : public QObject
{
    Q_OBJECT
private slots:
    void initDatabaseManager();
    void runDatabaseManager();
    void cleanDatabaseManager();

private:
    DatabaseManager *db;
};

#endif // DATABASEMANAGERTEST_H
