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
    QSignalSpy spyFragments(factory, SIGNAL(fragmentsReady(QList<LinkedConnectionFragment *>)));
    QSignalSpy spyPage(factory, SIGNAL(fragmentsReady(QList<LinkedConnectionFragment *>)));

    // Linked Connections page should be loaded from the SQLite DB (if this test already ran once)
    factory->getPage(QUrl("https://graph.irail.be/sncb/connections?departureTime=2018-07-21T07:29:00.000Z"));
    QVERIFY(spyFragments.wait(3000) || spyFragments.count() > 0); // spy.wait() won't work for sync code
    QVERIFY(spyPage.wait(3000) || spyPage.count() > 0); // spy.wait() won't work for sync code

    factory->getPage(QUrl("https://graph.irail.be/sncb/connections?departureTime=2018-07-21T08:14:00.000Z"));
    QVERIFY(spyFragments.wait(3000) || spyFragments.count() > 0); // spy.wait() won't work for sync code
    QVERIFY(spyPage.wait(3000) || spyPage.count() > 0); // spy.wait() won't work for sync code

    factory->getPage(QUrl("https://graph.irail.be/sncb/connections?departureTime=2018-07-21T06:45:00.000Z"));
    QVERIFY(spyFragments.wait(3000) || spyFragments.count() > 0); // spy.wait() won't work for sync code TODO
    QVERIFY(spyPage.wait(3000) || spyPage.count() > 0); // spy.wait() won't work for sync code

    // Linked Connections page should be loaded from the Linked Connections API (if it's a new page)
    factory->getPage(QUrl("https://graph.irail.be/sncb/connections?departureTime=" + QDateTime::currentDateTime().toString(Qt::ISODate)));
    QVERIFY(spyFragments.wait() || spyFragments.count() > 0);
    QVERIFY(spyPage.wait(3000) || spyPage.count() > 0);
}

void LinkedConnectionsFactoryTest::cleanLinkedConnectionsFactory()
{
    qDebug() << "Cleaning up factory";
    factory->deleteLater();
}
