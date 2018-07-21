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

#include "linkedconnection.h"

/**
 * @file httpmanager.cpp
 * @author Dylan Van Assche
 * @date 17 Jul 2018
 * @brief HTTPManager facade constructor
 * @public
 * Constructs a HTTPManager facade to access the network using the HTTP protocol.
 * The HTTPManager facade makes network access in Qt abstract from the underlying library (QNetworkAccessManager, libCurl, ...).
 */
LinkedConnection::LinkedConnection(QObject *parent) : QObject(parent)
{
    // Set parent of this QObject. When parent is destroyed, this one is automatically cleaned up too.
    this->setParent(parent);


}


// Getter & Setters
/**
 * @file linkedconnection.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Gets the URI of the linked connection
 * @return QUrl URI
 * @public
 * Retrieves the URI of the linked connection and returns it.
 */
QUrl LinkedConnection::uri() const
{
    return m_uri;
}

/**
 * @file linkedconnection.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Sets the URI of the linked connection
 * @param const QUrl &URI
 * @public
 * Sets the URI of the linked connection to the given QUrl &uri.
 */
void LinkedConnection::setURI(const QUrl &uri)
{
    m_uri = uri;
}

/**
 * @file linkedconnection.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Gets the departure station URI of the linked connection
 * @return QUrl departureStationURI
 * @public
 * Retrieves the departure station URI of the linked connection and returns it.
 */
QUrl LinkedConnection::departureStationURI() const
{
    return m_departureStationURI;
}

/**
 * @file linkedconnection.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Sets the departure station URI of the linked connection
 * @param const QUrl &departureStationURI
 * @public
 * Sets the departure station URI of the linked connection to the given QUrl &departureStationURI.
 */
void LinkedConnection::setDepartureStationURI(const QUrl &departureStationURI)
{
    m_departureStationURI = departureStationURI;
}

/**
 * @file linkedconnection.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Gets the arrival station URI of the linked connection
 * @return QUrl arrivalStationURI
 * @public
 * Retrieves the arrival station URI of the linked connection and returns it.
 */
QUrl LinkedConnection::arrivalStationURI() const
{
    return m_arrivalStationURI;
}

/**
 * @file linkedconnection.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Sets the arrival station URI of the linked connection
 * @param const QUrl &arrivalStationURI
 * @public
 * Sets the arrival station URI of the linked connection to the given QUrl &arrivalStationURI.
 */
void LinkedConnection::setArrivalStationURI(const QUrl &arrivalStationURI)
{
    m_arrivalStationURI = arrivalStationURI;
}

/**
 * @file linkedconnection.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Gets the departure time of the linked connection
 * @return QDateTime departureTime
 * @public
 * Retrieves the departure time of the linked connection and returns it.
 */
QDateTime LinkedConnection::departureTime() const
{
    return m_departureTime;
}

/**
 * @file linkedconnection.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Sets the departure time of the linked connection
 * @param const QDateTime &departureTime
 * @public
 * Sets the departure time of the linked connection to the given QDateTime &departureTime.
 */
void LinkedConnection::setDepartureTime(const QDateTime &departureTime)
{
    m_departureTime = departureTime;
}

/**
 * @file linkedconnection.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Gets the arrival time of the linked connection
 * @return QDateTime arrivalTime
 * @public
 * Retrieves the arrival time of the linked connection and returns it.
 */
QDateTime LinkedConnection::arrivalTime() const
{
    return m_arrivalTime;
}

/**
 * @file linkedconnection.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Sets the arrival time of the linked connection
 * @param const QDateTime &arrivalTime
 * @public
 * Sets the arrival time of the linked connection to the given QDateTime &arrivalTime.
 */
void LinkedConnection::setArrivalTime(const QDateTime &arrivalTime)
{
    m_arrivalTime = arrivalTime;
}

/**
 * @file linkedconnection.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Gets the departure delay of the linked connection
 * @return QDateTime departureDelay
 * @public
 * Retrieves the departure delay of the linked connection and returns it.
 */
qint16 LinkedConnection::departureDelay() const
{
    return m_departureDelay;
}

/**
 * @file linkedconnection.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Sets the departure delay of the linked connection
 * @param const QDateTime &departureDelay
 * @public
 * Sets the departure delay of the linked connection to the given qint16 &departureDelay.
 */
void LinkedConnection::setDepartureDelay(const qint16 &departureDelay)
{
    m_departureDelay = departureDelay;
}

/**
 * @file linkedconnection.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Gets the arrival delay of the linked connection
 * @return QDateTime arrivalDelay
 * @public
 * Retrieves the arrival delay of the linked connection and returns it.
 */
qint16 LinkedConnection::arrivalDelay() const
{
    return m_arrivalDelay;
}

/**
 * @file linkedconnection.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Sets the arrival delay of the linked connection
 * @param const QDateTime &arrival
 * @public
 * Sets the arrival delay of the linked connection to the given qint16 &arrivalDelay.
 */
void LinkedConnection::setArrivalDelay(const qint16 &arrivalDelay)
{
    m_arrivalDelay = arrivalDelay;
}

/**
 * @file linkedconnection.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Gets the trip URI of the linked connection
 * @return QUrl tripURI
 * @public
 * Retrieves the trip URI of the linked connection and returns it.
 */
QUrl LinkedConnection::tripURI() const
{
    return m_tripURI;
}

/**
 * @file linkedconnection.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Sets the trip URI of the linked connection
 * @param const QUrl &tripURI
 * @public
 * Sets the trip URI of the linked connection to the given QUrl &tripURI.
 */
void LinkedConnection::setTripURI(const QUrl &tripURI)
{
    m_tripURI = tripURI;
}

/**
 * @file linkedconnection.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Gets the route URI of the linked connection
 * @return QUrl routeURI
 * @public
 * Retrieves the route URI of the linked connection and returns it.
 */
QUrl LinkedConnection::routeURI() const
{
    return m_routeURI;
}

/**
 * @file linkedconnection.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Sets the route URI of the linked connection
 * @param const QUrl &routeURI
 * @public
 * Sets the route URI of the linked connection to the given QUrl &routeURI.
 */
void LinkedConnection::setRouteURI(const QUrl &routeURI)
{
    m_routeURI = routeURI;
}

/**
 * @file linkedconnection.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Gets the direction of the linked connection
 * @return QString direction
 * @public
 * Retrieves the direction of the vehicle in this linked connection and returns it.
 */
QString LinkedConnection::direction() const
{
    return m_direction;
}

/**
 * @file linkedconnection.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Sets the direction of the linked connection
 * @param const QString &direction
 * @public
 * Sets the direction of the vehicle in this linked connection to the given QString &direction.
 */
void LinkedConnection::setDirection(const QString &direction)
{
    m_direction = direction;
}
