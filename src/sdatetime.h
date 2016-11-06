#ifndef SDATETIME_H
#define SDATETIME_H

#include <QString>
#include <QObject>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(sdatetime)

class SDateTime
{
    Q_GADGET

    Q_PROPERTY(uint day MEMBER day)
    Q_PROPERTY(uint month MEMBER month)
    Q_PROPERTY(int year MEMBER year)
    Q_PROPERTY(uint second MEMBER second)
    Q_PROPERTY(uint minute MEMBER minute)
    Q_PROPERTY(uint hour MEMBER hour)

public:
    SDateTime();

    bool operator!=(const SDateTime &other) const {
        return !(day==other.day && month==other.month && year==other.year
                 && second==other.second && minute==other.minute
                 && hour==other.hour);
    }

    void fromString(const QString &dateTime);
    QString toString() const;

    uint day = 1;
    uint month = 1;
    int year = 1;
    uint second = 1;
    uint minute = 1;
    uint hour = 1;
};

#endif // SDATETIME_H
