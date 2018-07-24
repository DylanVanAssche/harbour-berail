/******************************************************************************
 * Copyright (C) 2018 by Dylan Van Assche                                     *
 *                                                                            *
 * This file is part of BeRail.                                               *
 *                                                                            *
 *   BeRail is free software: you can redistribute it and/or modify it        *
 *   under the terms of the GNU Lesser General Public License as published    *
 *   by the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                      *
 *                                                                            *
 *   BeRail is distributed in the hope that it will be useful,                *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 *   GNU Lesser General Public License for more details.                      *
 *                                                                            *
 *   You should have received a copy of the GNU Lesser General Public         *
 *   License along with BeRail.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************/

#include "linkedconnectionpagetest.h"

void LinkedConnectionPageTest::initLinkedConnectionPageTest()
{
    page = new LinkedConnectionPage(
                QUrl("https://graph.irail.be/sncb/connections?departureTime=2018-07-24T17:59:00.000Z"),
                QDateTime::fromString("2018-07-24T17:59:00.000Z", Qt::ISODate),
                QUrl("https://graph.irail.be/sncb/connections?departureTime=2018-07-24T16:29:00.000Z"),
                QUrl("https://graph.irail.be/sncb/connections?departureTime=2018-07-24T19:34:00.000Z"),
                this
                );
}

void LinkedConnectionPageTest::runLinkedConnectionPageTest()
{
    // Set each property and check if the signal of the property fires
    QSignalSpy spyUriChanged(page, SIGNAL(uriChanged()));
    page->setURI(QUrl("https://graph.irail.be/sncb/connections?departureTime=2018-07-24T16:29:00.000Z"));
    QCOMPARE(spyUriChanged.count(), 1);

    QSignalSpy spyTimestampChanged(page, SIGNAL(timestampChanged()));
    page->setTimestamp(QDateTime::fromString("2018-07-24T16:29:00.000Z", Qt::ISODate));
    QCOMPARE(spyTimestampChanged.count(), 1);

    QSignalSpy spyHydraNextChanged(page, SIGNAL(hydraNextChanged()));
    page->setHydraNext(QUrl("https://graph.irail.be/sncb/connections?departureTime=2018-07-24T15:29:00.000Z"));
    QCOMPARE(spyHydraNextChanged.count(), 1);

    QSignalSpy spyHydraPreviousChanged(page, SIGNAL(hydraPreviousChanged()));
    page->setHydraPrevious(QUrl("https://graph.irail.be/sncb/connections?departureTime=2018-07-24T17:29:00.000Z"));
    QCOMPARE(spyHydraPreviousChanged.count(), 1);
}

void LinkedConnectionPageTest::cleanLinkedConnectionPageTest()
{
    page->deleteLater();
}
