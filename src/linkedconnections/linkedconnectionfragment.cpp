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

#include "linkedconnectionfragment.h"

/**
 * @file linkedconnectionfragment.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief LinkedConnectionFragment constructor: empty
 * @param QObject *parent = nullptr
 * @public
 * Constructs a LinkedConnectionFragment to store the information about
 * a Linked Connection fragment for the Connection Scan Algorithm (CSA).
 */
LinkedConnectionFragment::LinkedConnectionFragment(QObject *parent) : QObject(parent)
{
    // Set parent of this QObject. When parent is destroyed, this one is automatically cleaned up too.
    this->setParent(parent);
}

/**
 * @file linkedconnectionfragment.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief LinkedConnectionFragment constructor: arrival and departure
 * @param const QUrl &uri
 * @param const QUrl &departureStationURI
 * @param const QUrl &arrivalStationURI
 * @param const QDateTime &departureTime
 * @param const QDateTime &arrivalTime
 * @param const qint16 &departureDelay
 * @param const qint16 &arrivalDelay
 * @param const QUrl &tripURI
 * @param const QUrl &routeURI
 * @param const QString &direction
 * @param QObject *parent = nullptr
 * @public
 * Constructs a LinkedConnectionFragment to store the information about
 * a Linked Connection fragment for the Connection Scan Algorithm (CSA).
 */
LinkedConnectionFragment::LinkedConnectionFragment(
        const QUrl &uri, const QUrl &departureStationURI,
        const QUrl &arrivalStationURI,
        const QDateTime &departureTime,
        const QDateTime &arrivalTime,
        const qint16 &departureDelay,
        const qint16 &arrivalDelay,
        const QUrl &tripURI,
        const QUrl &routeURI,
        const QString &direction,
        QObject *parent
        )
{
    // Set parent of this QObject. When parent is destroyed, this one is automatically cleaned up too.
    this->setParent(parent);

    // Avoid using setters in constructor to reduce signal emitting on instantiation.
    m_uri = uri;
    m_departureStationURI = departureStationURI;
    m_arrivalStationURI = arrivalStationURI;
    m_departureTime = departureTime;
    m_arrivalTime = arrivalTime;
    m_departureDelay = departureDelay;
    m_arrivalDelay = arrivalDelay;
    m_tripURI = tripURI;
    m_routeURI = routeURI;
    m_direction = direction;
}

// Getter & Setters
/**
 * @file linkedconnectionfragment.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Gets the URI of the linked connection fragment
 * @return QUrl URI
 * @public
 * Retrieves the URI of the linked connection fragment  and returns it.
 */
QUrl LinkedConnectionFragment::uri() const
{
    return m_uri;
}

/**
 * @file linkedconnectionfragment.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Sets the URI of the linked connection fragment
 * @param const QUrl &URI
 * @public
 * Sets the URI of the linked connection fragment to the given QUrl &uri.
 * Emits the uriChanged signal.
 */
void LinkedConnectionFragment::setURI(const QUrl &uri)
{
    m_uri = uri;
    emit this->uriChanged();
}

/**
 * @file linkedconnectionfragment.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Gets the departure station URI of the linked connection fragment
 * @return QUrl departureStationURI
 * @public
 * Retrieves the departure station URI of the linked connection fragment and returns it.
 */
QUrl LinkedConnectionFragment::departureStationURI() const
{
    return m_departureStationURI;
}

/**
 * @file linkedconnectionfragment.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Sets the departure station URI of the linked connection fragment
 * @param const QUrl &departureStationURI
 * @public
 * Sets the departure station URI of the linked connection fragment to the given QUrl &departureStationURI.
 * Emits the departureStationURIChanged signal.
 */
void LinkedConnectionFragment::setDepartureStationURI(const QUrl &departureStationURI)
{
    m_departureStationURI = departureStationURI;
    emit this->departureStationURIChanged();
}

/**
 * @file linkedconnectionfragment.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Gets the arrival station URI of the linked connection fragment
 * @return QUrl arrivalStationURI
 * @public
 * Retrieves the arrival station URI of the linked connection fragment and returns it.
 */
QUrl LinkedConnectionFragment::arrivalStationURI() const
{
    return m_arrivalStationURI;
}

/**
 * @file linkedconnectionfragment.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Sets the arrival station URI of the linked connection fragment
 * @param const QUrl &arrivalStationURI
 * @public
 * Sets the arrival station URI of the linked connection fragment to the given QUrl &arrivalStationURI.
 * Emits the arrivalStationURIChanged signal.
 */
void LinkedConnectionFragment::setArrivalStationURI(const QUrl &arrivalStationURI)
{
    m_arrivalStationURI = arrivalStationURI;
    emit this->arrivalStationURIChanged();
}

/**
 * @file linkedconnectionfragment.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Gets the departure time of the linked connection fragment
 * @return QDateTime departureTime
 * @public
 * Retrieves the departure time of the linked connection fragment and returns it.
 */
QDateTime LinkedConnectionFragment::departureTime() const
{
    return m_departureTime;
}

/**
 * @file linkedconnectionfragment.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Sets the departure time of the linked connection fragment
 * @param const QDateTime &departureTime
 * @public
 * Sets the departure time of the linked connection fragment to the given QDateTime &departureTime.
 * Emits the departureTimeChanged signal.
 */
void LinkedConnectionFragment::setDepartureTime(const QDateTime &departureTime)
{
    m_departureTime = departureTime;
    emit this->departureTimeChanged();
}

/**
 * @file linkedconnectionfragment.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Gets the arrival time of the linked connection fragment
 * @return QDateTime arrivalTime
 * @public
 * Retrieves the arrival time of the linked connection fragment and returns it.
 */
QDateTime LinkedConnectionFragment::arrivalTime() const
{
    return m_arrivalTime;
}

/**
 * @file linkedconnectionfragment.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Sets the arrival time of the linked connection fragment
 * @param const QDateTime &arrivalTime
 * @public
 * Sets the arrival time of the linked connection fragment to the given QDateTime &arrivalTime.
 * Emits the arrivalTimeChanged signal.
 */
void LinkedConnectionFragment::setArrivalTime(const QDateTime &arrivalTime)
{
    m_arrivalTime = arrivalTime;
    emit this->arrivalTimeChanged();
}

/**
 * @file linkedconnectionfragment.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Gets the departure delay of the linked connection fragment
 * @return QDateTime departureDelay
 * @public
 * Retrieves the departure delay of the linked connection fragment and returns it.
 */
qint16 LinkedConnectionFragment::departureDelay() const
{
    return m_departureDelay;
}

/**
 * @file linkedconnectionfragment.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Sets the departure delay of the linked connection fragment
 * @param const QDateTime &departureDelay
 * @public
 * Sets the departure delay of the linked connection fragment to the given qint16 &departureDelay.
 * Emits the departureDelayChanged signal.
 */
void LinkedConnectionFragment::setDepartureDelay(const qint16 &departureDelay)
{
    m_departureDelay = departureDelay;
    emit this->departureDelayChanged();
}

/**
 * @file linkedconnectionfragment.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Gets the arrival delay of the linked connection fragment
 * @return QDateTime arrivalDelay
 * @public
 * Retrieves the arrival delay of the linked connection fragment and returns it.
 */
qint16 LinkedConnectionFragment::arrivalDelay() const
{
    return m_arrivalDelay;
}

/**
 * @file linkedconnectionfragment.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Sets the arrival delay of the linked connection fragment
 * @param const QDateTime &arrival
 * @public
 * Sets the arrival delay of the linked connection fragment to the given qint16 &arrivalDelay.
 * Emits the arrivalDelayChanged signal.
 */
void LinkedConnectionFragment::setArrivalDelay(const qint16 &arrivalDelay)
{
    m_arrivalDelay = arrivalDelay;
    emit this->arrivalDelayChanged();
}

/**
 * @file linkedconnectionfragment.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Gets the trip URI of the linked connection fragment
 * @return QUrl tripURI
 * @public
 * Retrieves the trip URI of the linked connection fragment and returns it.
 */
QUrl LinkedConnectionFragment::tripURI() const
{
    return m_tripURI;
}

/**
 * @file linkedconnectionfragment.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Sets the trip URI of the linked connection fragment
 * @param const QUrl &tripURI
 * @public
 * Sets the trip URI of the linked connection fragment to the given QUrl &tripURI.
 * Emits the tripURIChanged signal.
 */
void LinkedConnectionFragment::setTripURI(const QUrl &tripURI)
{
    m_tripURI = tripURI;
    emit this->tripURIChanged();
}

/**
 * @file linkedconnectionfragment.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Gets the route URI of the linked connection fragment
 * @return QUrl routeURI
 * @public
 * Retrieves the route URI of the linked connection fragment and returns it.
 */
QUrl LinkedConnectionFragment::routeURI() const
{
    return m_routeURI;
}

/**
 * @file linkedconnectionfragment.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Sets the route URI of the linked connection fragment
 * @param const QUrl &routeURI
 * @public
 * Sets the route URI of the linked connection fragment to the given QUrl &routeURI.
 * Emits the routeURIChanged signal.
 */
void LinkedConnectionFragment::setRouteURI(const QUrl &routeURI)
{
    m_routeURI = routeURI;
    emit this->routeURIChanged();
}

/**
 * @file linkedconnectionfragment.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Gets the direction of the linked connection fragment
 * @return QString direction
 * @public
 * Retrieves the direction of the vehicle in this linked connection fragment and returns it.
 */
QString LinkedConnectionFragment::direction() const
{
    return m_direction;
}

/**
 * @file linkedconnectionfragment.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Sets the direction of the linked connection fragment
 * @param const QString &direction
 * @public
 * Sets the direction of the vehicle in this linked connection fragment to the given QString &direction.
 * Emits the directionChanged signal.
 */
void LinkedConnectionFragment::setDirection(const QString &direction)
{
    m_direction = direction;
    emit this->directionChanged();
}
