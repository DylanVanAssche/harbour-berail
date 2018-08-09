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

#ifndef CSASTATIONFACTORY_H
#define CSASTATIONFACTORY_H

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QStringList>
#include <QtSql/QSqlQuery>
#include "csastation.h"
#include "../../database/databasemanager.h"
#include "../qtcsv/include/qtcsv/stringdata.h"
#include "../qtcsv/include/qtcsv/reader.h"
#include "../qtcsv/include/qtcsv/writer.h"

#define DB_PATH "/home/nemo/.local/share/harbour-berail/db/stations.db"

namespace CSA {
class StationFactory : public QObject
{
    Q_OBJECT
public:
    static StationFactory *getInstance(QObject *parent = nullptr);
    Station *getStationByURI(const QUrl &uri);

private:
    Database::Manager *m_db;
    bool initDatabase();
    bool insertStationWithFacilitiesIntoDatabase(const QStringList &station, const QStringList &facilities);
    bool insertStationWithoutFacilitiesIntoDatabase(const QStringList &station);
    bool insertStopIntoDatabase(const QStringList &stop);
    Database::Manager *db() const;
    void setDb(Database::Manager *db);
    static CSA::StationFactory *m_instance;
    explicit StationFactory(QObject *parent);
};
}

#endif // CSASTATIONFACTORY_H