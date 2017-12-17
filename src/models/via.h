#ifndef VIA_H
#define VIA_H

#include <QtCore/QObject>
#include <QtCore/QString>

#include "stop.h"
#include "disturbances.h"

class Via: public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(Stop* arrival READ arrival WRITE setArrival NOTIFY arrivalChanged)
    Q_PROPERTY(Stop* departure READ departure WRITE setDeparture NOTIFY departureChanged)
    Q_PROPERTY(Station* station READ station WRITE setStation NOTIFY stationChanged)
    Q_PROPERTY(int timeBetween READ timeBetween WRITE setTimeBetween NOTIFY timeBetweenChanged)
    Q_PROPERTY(QString vehicleId READ vehicleId WRITE setVehicleId NOTIFY vehicleIdChanged)
    Q_PROPERTY(Disturbances* disturbances READ disturbances WRITE setDisturbances NOTIFY disturbancesChanged)

public:
    explicit Via(Stop* arrival, Stop* departure, Station* station, int timeBetween, QString vehicleId, Disturbances* disturbances);
    int id() const;
    void setId(int id);
    Stop *arrival() const;
    void setArrival(Stop *arrival);
    Stop *departure() const;
    void setDeparture(Stop *departure);
    Station *station() const;
    void setStation(Station *station);
    int timeBetween() const;
    void setTimeBetween(int timeBetween);
    QString vehicleId() const;
    void setVehicleId(const QString &vehicleId);
    Disturbances *disturbances() const;
    void setDisturbances(Disturbances *disturbances);

signals:
    void idChanged();
    void arrivalChanged();
    void departureChanged();
    void stationChanged();
    void timeBetweenChanged();
    void vehicleIdChanged();
    void disturbancesChanged();

private:
    int m_id;
    Stop* m_arrival;
    Stop* m_departure;
    Station* m_station;
    int m_timeBetween;
    QString m_vehicleId;
    Disturbances* m_disturbances;
};

#endif // VIA_H
