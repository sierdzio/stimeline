#include "scalendar.h"
#include "tags.h"

#include <QJsonValue>
#include <QJsonArray>

#include <QLoggingCategory>
#include <QDebug>
Q_LOGGING_CATEGORY(scalendar, "SCalendar")

SCalendar::SCalendar(QObject *parent) : QObject (parent)
{
    qCDebug(scalendar) << "Initializing default (Gregorian) calendar";
    checkValidity();
}

bool SCalendar::isValid() const
{
    return mIsValid;
}

QJsonArray SCalendar::toJson() const
{
    QJsonObject obj;

    obj.insert(Tags::name, QJsonValue(mName));
    // Date
    obj.insert(Tags::daysInWeek, QJsonValue(int(mDaysInWeek)));
    obj.insert(Tags::daysInYear, QJsonValue(int(mDaysInYear)));
    obj.insert(Tags::monthsInYear, QJsonValue(int(mMonthsInYear)));
    obj.insert(Tags::leapDayPerYear, QJsonValue(mLeapDayPerYear));
    obj.insert(Tags::leapDayAddsToMonthNumber, QJsonValue(int(mLeapDayAddsToMonthNumber)));
    // Months
    QJsonArray months;
    for (const SMonth &month: qAsConst(mMonths)) {
        months.append(QJsonValue(QJsonObject({{month.first, QJsonValue(int(month.second))}})));
    }
    obj.insert(Tags::months, months);
    // Time
    obj.insert(Tags::secondsInMinute, QJsonValue(int(mSecondsInMinute)));
    obj.insert(Tags::minutesInHour, QJsonValue(int(mMinutesInHour)));
    obj.insert(Tags::hoursInDay, QJsonValue(int(mHoursInDay)));

    QJsonArray result;
    result.append(obj);
    return result;
}

void SCalendar::fromJson(const QJsonArray &json)
{
    QJsonObject obj(json.first().toObject());
    mName = obj.value(Tags::name).toString();
    // Date
    mDaysInWeek = uint(obj.value(Tags::daysInWeek).toInt());
    mDaysInYear = uint(obj.value(Tags::daysInYear).toInt());
    mMonthsInYear = uint(obj.value(Tags::monthsInYear).toInt());
    mLeapDayPerYear = obj.value(Tags::leapDayPerYear).toDouble();
    mLeapDayAddsToMonthNumber = uint(obj.value(Tags::leapDayAddsToMonthNumber).toInt());
    // Months
    const QJsonArray months = obj.value(Tags::months).toArray();
    // TODO: check if order is preserved
    mMonths.clear();
    for (const QJsonValue &value: months) {
        const QJsonObject monthObj(value.toObject());
        const QString key(monthObj.keys().first());
        const SMonth month(key, uint(monthObj.value(key).toInt()));
        mMonths.append(month);
    }
    // Time
    mSecondsInMinute = uint(obj.value(Tags::secondsInMinute).toInt());
    mMinutesInHour = uint(obj.value(Tags::minutesInHour).toInt());
    mHoursInDay = uint(obj.value(Tags::hoursInDay).toInt());

    checkValidity();
    qCDebug(scalendar()) << mName << "calendar loaded. Valid:" << mIsValid;
}

/*!
 * Returns the number of days in given \a month.
 *
 * Month indexing starts with 0 (zero).
 */
uint SCalendar::daysInMonth(const uint month) const
{
    if (month > uint(mMonths.size())) {
        qCDebug(scalendar) << "Month number" << month << "exceeds number of months"
                           << "in a year";
        return 0;
    }

    return mMonths.at(int(month)).second;
}

/*!
 * Returns the name of the given \a month number.
 *
 * Month indexing starts with 0 (zero).
 */
QString SCalendar::monthName(const uint month) const
{
    if (month > uint(mMonths.size())) {
        qCDebug(scalendar) << "Month number" << month << "exceeds number of months"
                           << "in a year";
        return 0;
    }

    return mMonths.at(int(month)).first;
}

void SCalendar::checkValidity()
{
    mIsValid = true;
    uint daysInYear = 0;
    for (const SMonth &month: qAsConst(mMonths)) {
        daysInYear += month.second;
    }

    if (daysInYear != mDaysInYear) {
        qCDebug(scalendar) << "Days in year don't match!" << mDaysInYear
                           << "vs" << daysInYear;
    }
}

