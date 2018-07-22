#include "linkedconnectionsfactorytest.h"
#define DB_PATH "/home/nemo/.local/share/harbour-berail/db/lc-tests.db"

void LinkedConnectionsFactoryTest::initLinkedConnectionsFactory()
{
    qDebug() << "Init factory and populate fragments database";
    factory = LinkedConnectionsFactory::getInstance(DB_PATH);
}

void LinkedConnectionsFactoryTest::runLinkedConnectionsFactory()
{
    // Activate QSignalSpy
    QSignalSpy spy(factory, SIGNAL(fragmentsReady(QList<LinkedConnectionFragment *>)));

    // Linked Connections page should be loaded from the SQLite DB (if this test already ran once)
    factory->getPage(QUrl("https://graph.irail.be/sncb/connections?departureTime=2018-07-21T07:29:00.000Z"));
    QVERIFY(spy.wait() || spy.count() > 0); // seems to be a bug in QSignalSpy, sometimes wait() triggers and sometimes count() > 0

    // Linked Connections page should be loaded from the Linked Connections API (if it's a new page)
    factory->getPage(QUrl("https://graph.irail.be/sncb/connections?departureTime=" + QDateTime::currentDateTime().toString(Qt::ISODate)));
    QVERIFY(spy.wait() || spy.count() > 0);
}

void LinkedConnectionsFactoryTest::cleanLinkedConnectionsFactory()
{
    qDebug() << "Cleaning up factory";
    factory->deleteLater();
}
