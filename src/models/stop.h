#ifndef STOP_H
#define STOP_H

#include <QtCore/QObject>
#include <QtCore/QDateTime>
#include <QtCore/QString>

#include "station.h"
#include "enum.h"

// TO DO: isExtraStop property needs to be added
class Stop: public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(Station *station READ station WRITE setStation NOTIFY stationChanged)
    Q_PROPERTY(QString platform READ platform WRITE setPlatform NOTIFY platformChanged)
    Q_PROPERTY(bool isDefaultPlatform READ isDefaultPlatform WRITE setIsDefaultPlatform NOTIFY isDefaultPlatformChanged)
    Q_PROPERTY(int departureDelay READ departureDelay WRITE setDepartureDelay NOTIFY departureDelayChanged)
    Q_PROPERTY(QDateTime scheduledDepartureTime READ scheduledDepartureTime WRITE setScheduledDepartureTime NOTIFY scheduledDepartureTimeChanged)
    Q_PROPERTY(int arrivalDelay READ arrivalDelay WRITE setArrivalDelay NOTIFY arrivalDelayChanged)
    Q_PROPERTY(QDateTime scheduledArrivalTime READ scheduledArrivalTime WRITE setScheduledArrivalTime NOTIFY scheduledArrivalTimeChanged)
    Q_PROPERTY(bool left READ left WRITE setLeft NOTIFY leftChanged)

public:
    explicit Stop(int id,
                  Station* station,
                  QString platform,
                  bool isDefaultPlatform,
                  int departureDelay,
                  QDateTime scheduledDepartureTime,
                  bool departureCanceled,
                  int arrivalDelay,
                  QDateTime scheduledArrivalTime,
                  bool arrivalCanceled,
                  bool left,
                  Occupancy occupancy
                  );

    int id() const;
    void setId(int id);
    Station* station() const;
    void setStation(Station* station);
    QString platform() const;
    void setPlatform(const QString &platform);
    bool isDefaultPlatform() const;
    void setIsDefaultPlatform(bool isDefaultPlatform);
    int departureDelay() const;
    void setDepartureDelay(int departureDelay);
    QDateTime scheduledDepartureTime() const;
    void setScheduledDepartureTime(const QDateTime &scheduledDepartureTime);
    bool departureCanceled() const;
    void setDepartureCanceled(bool departureCanceled);
    int arrivalDelay() const;
    void setArrivalDelay(int arrivalDelay);
    QDateTime scheduledArrivalTime() const;
    void setScheduledArrivalTime(const QDateTime &scheduledArrivalTime);
    bool arrivalCanceled() const;
    void setArrivalCanceled(bool arrivalCanceled);
    bool left() const;
    void setLeft(bool left);
    Occupancy occupancy() const;
    void setOccupancy(const Occupancy &occupancy);

signals:
    void idChanged();
    void stationChanged();
    void platformChanged();
    void isDefaultPlatformChanged();
    void departureDelayChanged();
    void scheduledDepartureTimeChanged();
    void arrivalDelayChanged();
    void scheduledArrivalTimeChanged();
    void leftChanged();

private:
    int m_id;
    Station* m_station;
    QString m_platform;
    bool m_isDefaultPlatform;
    int m_departureDelay;
    QDateTime m_scheduledDepartureTime;
    bool m_departureCanceled;
    int m_arrivalDelay;
    QDateTime m_scheduledArrivalTime;
    bool m_arrivalCanceled;
    bool m_left;
    Occupancy m_occupancy;
};

#endif // STOP_H
