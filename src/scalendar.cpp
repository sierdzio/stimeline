#include "scalendar.h"
#include "sdatetime.h"
#include "tags.h"

#include <QJsonValue>
#include <QJsonArray>

#include <QLoggingCategory>
#include <QDebug>
Q_LOGGING_CATEGORY(scalendar, "SCalendar")

/*!
 * \class SCalendar
 *
 * STimeline supports arbitrary calendar types and SCalendar is a representation
 * of such system.
 *
 * The user can define any characteristics of the calendar:
 * \li how long the year is
 * \li month names and lenghts
 * \li leap days
 * \li week length
 * And many more.
 */

/*!
 * \property SCalendar::name
 *
 * Calendar name. Default is Gregorian.
 */

/*!
 * \property SCalendar::daysInWeek
 *
 * Number of days in a week. Default value is 7.
 */

/*!
 * \property SCalendar::daysInYear
 *
 * Number of days in a single (non-leap) year. Default is 356.
 */

/*!
 * \property SCalendar::monthsInYear
 *
 * Number of months in a single year. Default is 12.
 */

/*!
 * \property SCalendar::leapDayPerYear
 *
 * How much is a year longer than a full day. Default is 0.25 (so a leap year
 * happens every 4 years).
 */

/*!
 * \property SCalendar::leapDayAddsToMonthNumber
 *
 * Leap day should be added to this month number. Default is 2.
 */

/*!
 * \property SCalendar::secondsInMinute
 *
 * Number of seconds in a single minute. Default is 60.
 */

/*!
 * \property SCalendar::minutesInHour
 *
 * Number of minutes in a single hour. Default is 60
 */

/*!
 * \property SCalendar::hoursInDay
 *
 * Number of hours in a single day. Default is 24.
 */

/*!
 * Constructor - initializes the default Gregorian calendar. Accepts a QObject
 * \a parent.
 */
SCalendar::SCalendar(QObject *parent) : QObject (parent)
{
    qCDebug(scalendar) << "Initializing default (Gregorian) calendar";
    checkValidity();
}

/*!
 * Returns true if the calendar definition is valid.
 *
 * A calendar can be invalid when number of days in year does not match summarized
 * days from all months, for example.
 *
 * \sa checkValidity
 */
bool SCalendar::isValid() const
{
    return mIsValid;
}

/*!
 * Returns a JSON representation of current calendar system.
 */
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

/*!
 * Loads calendar definition from \a json.
 */
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

/*!
 * Returns duration (in seconds) between \a from and \a to dates, based on
 * calendar this SCalendar instance points to.
 *
 * This method is computationally intensive, please use it wisely.
 */
quint64 SCalendar::duration(const SDateTime &from, const SDateTime &to) const
{
    const quint64 fromSeconds = secondsInDateTime(from);
    const quint64 toSeconds = secondsInDateTime(to);

    // TODO: check if that works correctly (correct range calculation)
    return qAbs(toSeconds - fromSeconds);
}

/*!
 * Retuns number of seconds between zero date (0-0-0 0:0:0) and \a dateTime,
 * based on this SCalendar instance definition of calendar.
 *
 * WARNING: method does not check for out of bounds error.
 */
quint64 SCalendar::secondsInDateTime(const SDateTime &dateTime) const
{
    // Secs
    quint64 result = dateTime.second;
    // Minutes
    result += dateTime.minute * mSecondsInMinute;
    // Hours
    const quint64 secondsInHour = mMinutesInHour * mSecondsInMinute;
    result += dateTime.hour * secondsInHour;
    // Days
    const quint64 secondsInDay = secondsInHour * mHoursInDay;
    result += dateTime.day * secondsInDay;
    // Months
    const quint64 secondsInMonth = secondsInDay * daysInMonth(dateTime.month);
    result += dateTime.month * secondsInMonth;
    // Years
    const quint64 secondsInYear = secondsInDay * mDaysInYear;
    result += quint64(dateTime.year) * secondsInYear;
    return result;
}

/*!
 * Checks if calendar definition is sound.
 *
 * Modifies internal state. To check the result, use isValid().
 *
 * \sa isValid
 */
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

