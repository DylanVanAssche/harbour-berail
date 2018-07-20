#
#   This file is part of BeRail.
#
#   BeRail is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   BeRail is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with BeRail.  If not, see <http://www.gnu.org/licenses/>.
#

# The name of your application
TARGET = harbour-berail

CONFIG += sailfishapp

QT += core \
    network \
    positioning \
    testlib \
    sql

# OS module notification support
PKGCONFIG += nemonotifications-qt5
QT += dbus

# Disable debug and warning messages while releasing for security reasons
CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT \
QT_NO_WARNING_OUTPUT

# APP_VERSION retrieved from .spec file
DEFINES += APP_VERSION=\"\\\"$${VERSION}\\\"\"

SAILFISHAPP_ICONS = 86x86 108x108 128x128 256x256

# Enable translations
CONFIG += sailfishapp_i18n \
    sailfishapp_i18n_idbased

TRANSLATIONS += translations/harbour-berail.ts \
translations/harbour-berail-de.ts \
translations/harbour-berail-nl.ts

DISTFILES += \
    qml/pages/AboutPage.qml \
    qml/pages/TextLabel.qml \
    qml/pages/GlassButton.qml \
    qml/resources/icons/icon-translate.png \
    qml/resources/icons/icon-paypal.png \
    qml/resources/icons/icon-github.png \
    qml/resources/icons/icon-fontawesome.png \
    qml/resources/icons/icon-code.png \
    qml/pages/components/TextLabel.qml \
    qml/pages/components/GlassButton.qml \
    qml/pages/js/station.js \
    qml/pages/StationListPage.qml \
    qml/pages/js/util.js \
    qml/pages/DatePickerPage.qml \
    qml/pages/components/TripItem.qml \
    qml/pages/js/trip.js \
    qml/pages/components/LiveBoardItem.qml \
    qml/pages/components/CancelOverlay.qml \
    qml/pages/js/liveboard.js \
    qml/pages/components/LoadIndicator.qml \
    qml/pages/LiveboardPage.qml \
    rpm/harbour-berail.changes \
    qml/pages/js/disturbances.js \
    qml/pages/components/DisturbancesView.qml \
    qml/pages/DisturbancesPage.qml \
    qml/pages/SettingsPage.qml \
    qml/components/GlassStationButton.qml \
    qml/pages/TripDetailHeader.qml

RESOURCES += \
    qml/resources/resources.qrc

HEADERS += \
    src/logger.h \
    src/os.h \
    src/database/databasemanager.h \
    src/network/httpmanager.h \
    src/models/connection.h \
    tests/httpmanagertest.h \
    tests/databasemanagertest.h

SOURCES += src/harbour-berail.cpp \
    src/logger.cpp \
    src/os.cpp \
    src/database/databasemanager.cpp \
    src/network/httpmanager.cpp \
    src/models/connection.cpp \
    tests/httpmanagertest.cpp \
    tests/databasemanagertest.cpp

OTHER_FILES += qml/harbour-berail.qml \
    qml/cover/CoverPage.qml \
    qml/pages/FirstPage.qml \
    rpm/harbour-berail.spec \
    rpm/harbour-berail.yaml \
    translations/*.ts \
    harbour-berail.desktop
