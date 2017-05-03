#pragma once

#include <QString>
#include <QObject>
#include <QVector>
#include <QPair>
#include <QJsonObject>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(scalendar)

class SDateTime;

using SMonth = QPair<QString, uint>;

class SCalendar : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name MEMBER mName NOTIFY nameChanged)
    Q_PROPERTY(QString defaultDateTime MEMBER mDefaultDateTime NOTIFY defaultDateTimeChanged)
    Q_PROPERTY(uint daysInWeek MEMBER mDaysInWeek NOTIFY daysInWeekChanged)
    Q_PROPERTY(uint daysInYear MEMBER mDaysInYear NOTIFY daysInYearChanged)
    Q_PROPERTY(uint monthsInYear MEMBER mMonthsInYear NOTIFY monthsInYearChanged)
    Q_PROPERTY(qreal leapDayPerYear MEMBER mLeapDayPerYear NOTIFY leapDayPerYearChanged)
    Q_PROPERTY(uint leapDayAddsToMonthNumber MEMBER mLeapDayAddsToMonthNumber NOTIFY leapDayAddsToMonthNumberChanged)
    Q_PROPERTY(uint secondsInMinute MEMBER mSecondsInMinute NOTIFY secondsInMinuteChanged)
    Q_PROPERTY(uint minutesInHour MEMBER mMinutesInHour NOTIFY minutesInHourChanged)
    Q_PROPERTY(uint hoursInDay MEMBER mHoursInDay NOTIFY hoursInDayChanged)

    friend class SCalendarTest;

public:
    SCalendar(QObject *parent = nullptr);
    bool isValid() const;

    QJsonArray toJson() const;
    void fromJson(const QJsonArray &json);

    Q_INVOKABLE uint daysInMonth(const uint month) const;
    Q_INVOKABLE void setDaysInMonth(const uint month, const uint days);
    Q_INVOKABLE QString monthName(const uint month) const;
    Q_INVOKABLE void setMonthName(const uint month, const QString &name);
    Q_INVOKABLE bool isEarlier(const QString &date, const QString &other) const;

    quint64 duration(const SDateTime &from, const SDateTime &to) const;
    quint64 secondsInDateTime(const SDateTime &dateTime) const;

signals:
    void nameChanged(const QString &name) const; //!< Indicates name change
    void daysInWeekChanged(uint daysInWeek) const; //!< K
    void daysInYearChanged(uint daysInYear) const; //!< K
    void monthsInYearChanged(uint monthsInYear) const; //!< K
    void leapDayPerYearChanged(qreal leapDayPerYear) const; //!< K
    void leapDayAddsToMonthNumberChanged(uint leapDayAddsToMonthNumber) const; //!< K
    void secondsInMinuteChanged(uint secondsInMinute) const; //!< K
    void minutesInHourChanged(uint minutesInHour) const; //!< K
    void hoursInDayChanged(uint hoursInDay) const; //!< K    
    void defaultDateTimeChanged(const QString &defaultDateTime) const; //!< K

private:
    void checkValidity();

    bool mIsValid = false;

    QString mName = "Gregorian";
    QString mDefaultDateTime = "2017-1-1 0:0:0";

    // Date
    uint mDaysInWeek = 7;
    uint mDaysInYear = 365;
    uint mMonthsInYear = 12;
    qreal mLeapDayPerYear = 0.2425; //0.25;
    uint mLeapDayAddsToMonthNumber = 2;

    // Months
    QVector<SMonth> mMonths = {
        {"January", 31},
        {"February", 28},
        {"March", 31},
        {"April", 30},
        {"May", 31},
        {"June", 30},
        {"July", 31},
        {"August", 31},
        {"September", 30},
        {"October", 31},
        {"November", 30},
        {"December", 31}
    };

    // Time
    uint mSecondsInMinute = 60;
    uint mMinutesInHour = 60;
    uint mHoursInDay = 24;
};
