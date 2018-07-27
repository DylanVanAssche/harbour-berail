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

#include "linkedconnectionpage.h"

/**
 * @file linkedconnectionpage.cpp
 * @author Dylan Van Assche
 * @date 24 Jul 2018
 * @brief LinkedConnectionPage constructor: empty
 * @param QObject *parent = nullptr
 * @public
 * Constructs a LinkedConnectionPage to store the information about
 * a Linked Connection page for the Connection Scan Algorithm (CSA).
 */
LinkedConnectionPage::LinkedConnectionPage(QObject *parent) : QObject(parent)
{
    // Set parent of this QObject. When parent is destroyed, this one is automatically cleaned up too.
    this->setParent(parent);
}

/**
 * @file linkedconnectionpage.cpp
 * @author Dylan Van Assche
 * @date 24 Jul 2018
 * @brief LinkedConnectionPage constructor: page with the next and previous URIs
 * @param const QUrl &uri
 * @param const QDateTime &timestamp
 * @param const QUrl &hydraNext
 * @param const QUrl &hydraPrevious
 * @param QObject *parent = nullptr
 * @public
 * Constructs a LinkedConnectionPage to store the information about
 * a Linked Connection page for the Connection Scan Algorithm (CSA).
 */
LinkedConnectionPage::LinkedConnectionPage(const QUrl &uri, const QDateTime &timestamp, const QUrl &hydraNext, const QUrl &hydraPrevious, const QList<LinkedConnectionFragment *> &fragments, QObject *parent)
{
    // Avoid signal triggering on contruction
    m_uri = uri;
    m_timestamp = timestamp;
    m_hydraNext = hydraNext;
    m_hydraPrevious = hydraPrevious;
    m_fragments = fragments;

    // Set parent of this QObject. When parent is destroyed, this one is automatically cleaned up too.
    this->setParent(parent);
}

/**
 * @file linkedconnectionpage.cpp
 * @author Dylan Van Assche
 * @date 24 Jul 2018
 * @brief Gets the URI of the linked connection page
 * @return QUrl URI
 * @public
 * Retrieves the URI of the linked connection page and returns it.
 */
QUrl LinkedConnectionPage::uri() const
{
    return m_uri;
}

/**
 * @file linkedconnectionpage.cpp
 * @author Dylan Van Assche
 * @date 24 Jul 2018
 * @brief Sets the URI of the linked connection page
 * @param const QUrl &URI
 * @public
 * Sets the URI of the linked connection page to the given QUrl &uri.
 * Emits the uriChanged signal.
 */
void LinkedConnectionPage::setURI(const QUrl &uri)
{
    m_uri = uri;
    emit this->uriChanged();
}

/**
 * @file linkedconnectionpage.cpp
 * @author Dylan Van Assche
 * @date 24 Jul 2018
 * @brief Gets the timestamp of the linked connection page
 * @return QDateTime timestamp
 * @public
 * Retrieves the timestamp of the linked connection page and returns it.
 */
QDateTime LinkedConnectionPage::timestamp() const
{
    return m_timestamp;
}

/**
 * @file linkedconnectionpage.cpp
 * @author Dylan Van Assche
 * @date 24 Jul 2018
 * @brief Sets the timestamp of the linked connection fragment
 * @param const QDateTime &timestamp
 * @public
 * Sets the timestamp of the linked connection fragment to the given QDateTime &timestamp.
 * Emits the timestampChanged signal.
 */
void LinkedConnectionPage::setTimestamp(const QDateTime &timestamp)
{
    m_timestamp = timestamp;
    emit this->timestampChanged();
}

/**
 * @file linkedconnectionpage.cpp
 * @author Dylan Van Assche
 * @date 24 Jul 2018
 * @brief Gets the URI of the next linked connection page
 * @return QUrl URI
 * @public
 * Retrieves the URI of the next linked connection page and returns it.
 */
QUrl LinkedConnectionPage::hydraNext() const
{
    return m_hydraNext;
}

/**
 * @file linkedconnectionpage.cpp
 * @author Dylan Van Assche
 * @date 24 Jul 2018
 * @brief Sets the URI of the linked connection next page
 * @param const QUrl &hydraPrevious
 * @public
 * Sets the URI of the linked connection next page to the given QUrl &hydraPrevious.
 * Emits the hydraPreviousChanged signal.
 */
void LinkedConnectionPage::setHydraNext(const QUrl &hydraNext)
{
    m_hydraNext = hydraNext;
    emit this->hydraNextChanged();
}

/**
 * @file linkedconnectionpage.cpp
 * @author Dylan Van Assche
 * @date 24 Jul 2018
 * @brief Gets the URI of the previous linked connection page
 * @return QUrl URI
 * @public
 * Retrieves the URI of the previous linked connection page and returns it.
 */
QUrl LinkedConnectionPage::hydraPrevious() const
{
    return m_hydraPrevious;
}

/**
 * @file linkedconnectionpage.cpp
 * @author Dylan Van Assche
 * @date 24 Jul 2018
 * @brief Sets the URI of the linked connection previous page
 * @param const QUrl &hydraPrevious
 * @public
 * Sets the URI of the linked connection previous page to the given QUrl &hydraPrevious.
 * Emits the hydraPreviousChanged signal.
 */
void LinkedConnectionPage::setHydraPrevious(const QUrl &hydraPrevious)
{
    m_hydraPrevious = hydraPrevious;
    emit this->hydraPreviousChanged();
}

/**
 * @file linkedconnectionpage.cpp
 * @author Dylan Van Assche
 * @date 27 Jul 2018
 * @brief Gets the list of fragments associated with this page
 * @return QList<LinkedConnectionFragment *> fragments
 * @public
 * Gets the list of fragments associated with this page and return it.
 */
QList<LinkedConnectionFragment *> LinkedConnectionPage::fragments() const
{
    return m_fragments;
}

/**
 * @file linkedconnectionpage.cpp
 * @author Dylan Van Assche
 * @date 27 Jul 2018
 * @brief  Sets the list of fragments associated with this page
 * @param const QList<LinkedConnectionFragment *> &fragments
 * @public
 * Sets the list of fragments associated with this page to the given QList<LinkedConnectionFragment *> &fragments.
 * Emits the fragmentsChanged signal.
 */
void LinkedConnectionPage::setFragments(const QList<LinkedConnectionFragment *> &fragments)
{
    m_fragments = fragments;
    emit this->fragmentsChanged();
}
