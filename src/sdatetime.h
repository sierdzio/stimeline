#pragma once

#include <QString>
#include <QByteArray>
#include <QObject>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(sdatetime)

class SDateTime
{
    Q_GADGET

    Q_PROPERTY(uint day READ day WRITE setDay)
    Q_PROPERTY(uint month READ month WRITE setMonth)
    Q_PROPERTY(int year READ year WRITE setYear)
    Q_PROPERTY(uint second READ second WRITE setSecond)
    Q_PROPERTY(uint minute READ minute WRITE setMinute)
    Q_PROPERTY(uint hour READ hour WRITE setHour)

public:
    SDateTime();
    SDateTime(const QString &dateTimeString);

    bool operator!=(const SDateTime &other) const;
    bool operator<(const SDateTime &other) const;

    static SDateTime fromString(const QByteArray &dateTime);
    Q_INVOKABLE static SDateTime fromString(const QString &dateTime);
    Q_INVOKABLE QString toString() const;

    uint day() const;
    uint month() const;
    int year() const;
    uint second() const;
    uint minute() const;
    uint hour() const;

public slots:
    void setDay(const uint day);
    void setMonth(const uint month);
    void setYear(const int year);
    void setSecond(const uint second);
    void setMinute(const uint minute);
    void setHour(const uint hour);

private:
    void updateStringRepresentation();

    QByteArray mStringRepresentation;
    uint mDay = 1;
    uint mMonth = 1;
    int mYear = 1;
    uint mSecond = 1;
    uint mMinute = 1;
    uint mHour = 1;
};
