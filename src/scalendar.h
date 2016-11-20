#ifndef SCALENDAR_H
#define SCALENDAR_H

#include <QString>
#include <QObject>
#include <QVector>
#include <QPair>
#include <QJsonObject>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(scalendar)

using SMonth = QPair<QString, uint>;

class SCalendar : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name MEMBER mName NOTIFY nameChanged)
    Q_PROPERTY(uint daysInWeek MEMBER mDaysInWeek NOTIFY daysInWeekChanged)
    Q_PROPERTY(uint daysInYear MEMBER mDaysInYear NOTIFY daysInYearChanged)
    Q_PROPERTY(uint monthsInYear MEMBER mMonthsInYear NOTIFY monthsInYearChanged)
    Q_PROPERTY(qreal leapDayPerYear MEMBER mLeapDayPerYear NOTIFY leapDayPerYearChanged)
    Q_PROPERTY(uint leapDayAddsToMonthNumber MEMBER mLeapDayAddsToMonthNumber NOTIFY leapDayAddsToMonthNumberChanged)
    Q_PROPERTY(uint secondsInMinute MEMBER mSecondsInMinute NOTIFY secondsInMinuteChanged)
    Q_PROPERTY(uint minutesInHour MEMBER mMinutesInHour NOTIFY minutesInHourChanged)
    Q_PROPERTY(uint hoursInDay MEMBER mHoursInDay NOTIFY hoursInDayChanged)

public:
    SCalendar(QObject *parent = nullptr);
    bool isValid() const;

    QJsonArray toJson() const;
    void fromJson(const QJsonArray &json);

    Q_INVOKABLE uint daysInMonth(const uint month) const;
    Q_INVOKABLE QString monthName(const uint month) const;

signals:
    void nameChanged(const QString &name) const;
    void daysInWeekChanged(uint daysInWeek) const;
    void daysInYearChanged(uint daysInYear) const;
    void monthsInYearChanged(uint monthsInYear) const;
    void leapDayPerYearChanged(qreal leapDayPerYear) const;
    void leapDayAddsToMonthNumberChanged(uint leapDayAddsToMonthNumber) const;
    void secondsInMinuteChanged(uint secondsInMinute) const;
    void minutesInHourChanged(uint minutesInHour) const;
    void hoursInDayChanged(uint hoursInDay) const;

private:
    void checkValidity();

    bool mIsValid = false;

    QString mName = "Gregorian";
    // Date
    uint mDaysInWeek = 7;
    uint mDaysInYear = 365;
    uint mMonthsInYear = 12;
    qreal mLeapDayPerYear = 0.25;
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
    QString m_name;
    uint m_daysInWeek;
    uint m_daysInYear;
    uint m_monthsInYear;
    qreal m_leapDayPerYear;
    uint m_leapDayAddsToMonthNumber;
    uint m_secondsInMinute;
    uint m_minutesInHour;
    uint m_hoursInDay;
};

#endif // SCALENDAR_H
