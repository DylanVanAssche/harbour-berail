#include "linkedconnectionsfactorytest.h"

void LinkedConnectionsFactoryTest::initLinkedConnectionsFactory()
{
    qDebug() << "Init factory and populate fragments database";

    // Due the singleton pattern we will automatically connect to the same DB as the factory.
    db = DatabaseManager::getInstance("~/.local/share/harbour-berail/db/linkedconnections-test.db");
    QSqlQuery query(db->database());
    query.prepare("DROP TABLE IF EXISTS fragments"); // Dropping is needed to run the tests multiple times
    db->execute(query);

    // Create factory
    factory = LinkedConnectionsFactory::getInstance("~/.local/share/harbour-berail/db/linkedconnections-test.db");

}

void LinkedConnectionsFactoryTest::runLinkedConnectionsFactory()
{
    // Insert 2 records into the fragments TABLE for testing purposes
    QSqlQuery query(db->database());

    // Connection without delay
    QVERIFY(query.prepare("INSERT INTO fragments ("
                          "uri,"
                          "departureStationURI,"
                          "arrivalStationURI,"
                          "departureTime,"
                          "arrivalTime,"
                          "departureDelay,"
                          "arrivalDelay,"
                          "tripURI,"
                          "routeURI,"
                          "direction)"
                          " VALUES(:uri, "
                          ":departureStationURI,"
                          ":arrivalStationURI,"
                          ":departureTime,"
                          ":arrivalTime,"
                          ":departureDelay,"
                          ":arrivalDelay,"
                          ":tripURI,"
                          ":routeURI,"
                          ":direction)"));
    // Input data, see linkedconnectionfragmenttest.cpp
    query.bindValue(":uri", "http://irail.be/connections/8822004/20180721/IC3108");
    query.bindValue(":departureStationURI", "http://irail.be/stations/NMBS/008822004");
    query.bindValue(":arrivalStationURI", "http://irail.be/stations/NMBS/008822343");
    query.bindValue(":departureTime", "2018-07-21T07:29:00.000Z");
    query.bindValue(":arrivalTime", "2018-07-21T07:32:00.000Z");
    query.bindValue(":departureDelay", 0);
    query.bindValue(":arrivalDelay", 0);
    query.bindValue(":tripURI", "http://irail.be/vehicle/IC3108/20180721");
    query.bindValue(":routeURI", "http://irail.be/vehicle/IC3108");
    query.bindValue(":direction", "Anvers-Central");
    QVERIFY(db->execute(query));
    query.clear(); // Release resources for further reuse

    // Connection with delay
    QVERIFY(query.prepare("INSERT INTO fragments(uri,"
                          "departureStationURI,"
                          "arrivalStationURI,"
                          "departureTime,"
                          "arrivalTime,"
                          "departureDelay,"
                          "arrivalDelay,"
                          "tripURI,"
                          "routeURI,"
                          "direction)"
                          " VALUES(:uri, "
                          ":departureStationURI,"
                          ":arrivalStationURI,"
                          ":departureTime,"
                          ":arrivalTime,"
                          ":departureDelay,"
                          ":arrivalDelay,"
                          ":tripURI,"
                          ":routeURI,"
                          ":direction)"));
    // Input data, see linkedconnectionfragmenttest.cpp
    query.bindValue(":uri", "http://irail.be/connections/8814001/20180721/IC3309");
    query.bindValue(":departureStationURI", "http://irail.be/stations/NMBS/008814001");
    query.bindValue(":arrivalStationURI", "http://irail.be/stations/NMBS/008813037");
    query.bindValue(":departureTime", "2018-07-21T07:29:00.000Z");
    query.bindValue(":arrivalTime", "2018-07-21T07:31:00.000Z");
    query.bindValue(":departureDelay", 0);
    query.bindValue(":arrivalDelay", 60);
    query.bindValue(":tripURI", "http://irail.be/vehicle/IC3309/20180721");
    query.bindValue(":routeURI", "http://irail.be/vehicle/IC3309");
    query.bindValue(":direction", "Anvers-Central");
    QVERIFY(db->execute(query));
    query.clear();

    LinkedConnectionFragment *fragment = factory->getFragment(QUrl("http://irail.be/connections/8822004/20180721/IC3108"));
    QCOMPARE(fragment->uri(), QUrl("http://irail.be/connections/8822004/20180721/IC3108"));
    QCOMPARE(fragment->departureStationURI(), QUrl("http://irail.be/stations/NMBS/008822004"));
    QCOMPARE(fragment->arrivalStationURI(), QUrl("http://irail.be/stations/NMBS/008822343"));
    QCOMPARE(fragment->departureTime(), QDateTime::fromString("2018-07-21T07:29:00.000Z", Qt::ISODate));
    QCOMPARE(fragment->arrivalTime(), QDateTime::fromString("2018-07-21T07:32:00.000Z", Qt::ISODate));
    QCOMPARE(fragment->departureDelay(), qint16(0));
    QCOMPARE(fragment->arrivalDelay(), qint16(0));
    QCOMPARE(fragment->tripURI(), QUrl("http://irail.be/vehicle/IC3108/20180721"));
    QCOMPARE(fragment->routeURI(), QUrl("http://irail.be/vehicle/IC3108"));
    QCOMPARE(fragment->direction(), QString("Anvers-Central"));
}

void LinkedConnectionsFactoryTest::cleanLinkedConnectionsFactory()
{
    qDebug() << "Cleaning up factory";
    factory->deleteLater();
}
