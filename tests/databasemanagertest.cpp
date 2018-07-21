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

#include "databasemanagertest.h"

void DatabaseManagerTest::initDatabaseManager()
{
    db = DatabaseManager::getInstance("/home/nemo/.local/share/harbour-berail/db/tests.db");
}

void DatabaseManagerTest::runDatabaseManager()
{
    // Create a QSqlQuery object and connect it to our database
    QSqlQuery query(db->database());

    // Drop test TABLE if exists
    QVERIFY(query.prepare("DROP TABLE IF EXISTS people")); // Preparing is succesfull when method returns true
    QVERIFY(db->execute(query));
    query.clear(); // Release resources for reuse

    // Create test TABLE
    QVERIFY(query.prepare("CREATE TABLE people (id INTEGER PRIMARY KEY, name TEXT)")); // Preparing is succesfull when method returns true
    QVERIFY(db->execute(query));
    query.clear(); // Release resources for reuse

    // Insert into TABLE
    QVERIFY(query.prepare("INSERT INTO people(id, name) VALUES(1, 'Kara Zor-El')"));
    QVERIFY(db->execute(query));
    query.clear();

    // Read from TABLE
    QVERIFY(query.prepare("SELECT name FROM people WHERE id = ?"));
    query.addBindValue(1); // ID = 1 for Kara Zor-El
    QVERIFY(db->execute(query));
    if(query.first()) { // Only 1 result is returned, use a while loop for multiple results
        QString result = query.value(0).toString();
        qDebug() << result;
        QVERIFY(result.length() > 0);
    }
    else {
        QFAIL("ID not found in database!");
    }
    query.clear();
}

void DatabaseManagerTest::cleanDatabaseManager()
{
    db->deleteLater();
}
