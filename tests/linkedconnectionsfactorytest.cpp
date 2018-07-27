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
    //qRegisterMetaType<LinkedConnectionPage>(); // register custom class
    //QSignalSpy spyPage(factory, SIGNAL(pageReady(LinkedConnectionPage*)));

    // Linked Connections page should be loaded from the SQLite DB (if this test already ran once)
    factory->getPage(QUrl("https://graph.irail.be/sncb/connections?departureTime=2018-07-21T07:29:00.000Z"));
    //QVERIFY(spyPage.wait(3000));

    factory->getPage(QUrl("https://graph.irail.be/sncb/connections?departureTime=2018-07-21T08:14:00.000Z"));
    //QVERIFY(spyPage.wait(3000));

    factory->getPage(QUrl("https://graph.irail.be/sncb/connections?departureTime=2018-07-21T06:45:00.000Z"));
    //QVERIFY(spyPage.wait(3000));

    // Linked Connections page should be loaded from the Linked Connections API (if it's a new page)
    factory->getPage(QDateTime::currentDateTime());
    //QVERIFY(spyPage.wait(3000));
}

void LinkedConnectionsFactoryTest::cleanLinkedConnectionsFactory()
{
    qDebug() << "Cleaning up factory";
    factory->deleteLater();
}
