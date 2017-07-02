#include "sdatetime.h"
#include "tags.h"

#include <QStringList>

#include <QLoggingCategory>
#include <QDebug>
Q_LOGGING_CATEGORY(sdatetime, "SDateTime")

/*!
 * \class SDateTime
 *
 * Represents a certain point in time. Implementation is SCalendar-agnostic and
 * can work with any calendar system.
 *
 * \todo Currently SDT does not add leading zeros to dates and times, so it
 * puts out "2017-4-30 13:6:59" instead of "2017-04-30 13:06:59"
 */

/*!
 * \property SDateTime::day
 *
 * Current day of the month.
 */

/*!
 * \property SDateTime::month
 *
 * Current month of the year.
 */

/*!
 * \property SDateTime::year
 *
 * Current year.
 */

/*!
 * \property SDateTime::second
 *
 * Current second.
 */

/*!
 * \property SDateTime::minute
 *
 * Current minute.
 */

/*!
 * \property SDateTime::hour
 *
 * Current hour.
 */

/*!
 * Default constructor. Nothing interesting.
 */
SDateTime::SDateTime()
{
    updateStringRepresentation();
}

/*!
 * Constructs a SDateTime object from \a dateTimeString.
 */
SDateTime::SDateTime(const QString &dateTimeString)
{
    if (dateTimeString.isEmpty()) {
        qDebug(sdatetime) << "DateTime is empty!";
        return;
    }

    // "1234-12-24 11:11:11"
    const QStringList dateAndTime(dateTimeString.split(QLatin1String(" "),
                                                       QString::KeepEmptyParts,
                                                       Qt::CaseSensitive));

    if (dateAndTime.length() != 2) {
        qCDebug(sdatetime) << "DateTime parsing error!" << dateAndTime;
        return;
    }

    const QString date(dateAndTime.first());
    const QString time(dateAndTime.at(1));

    // Date
    const QStringList dateDivided(date.split(Tags::dateSeparator,
                                             QString::KeepEmptyParts,
                                             Qt::CaseSensitive));
    if (dateDivided.length() != 3) {
        qCDebug(sdatetime) << "Date parsing error!" << dateDivided;
        return;
    }

    mYear = dateDivided.at(0).toInt();
    mMonth = dateDivided.at(1).toUInt();
    mDay = dateDivided.at(2).toUInt();

    // Time
    const QStringList timeDivided(time.split(Tags::timeSeparator,
                                             QString::KeepEmptyParts,
                                             Qt::CaseSensitive));
    if (timeDivided.length() != 3) {
        qCDebug(sdatetime) << "Time parsing error!" << timeDivided;
        return;
    }

    mHour = timeDivided.at(0).toUInt();
    mMinute = timeDivided.at(1).toUInt();
    mSecond = timeDivided.at(2).toUInt();
    updateStringRepresentation();
    //qCDebug(sdatetime) << "Date parsed!" << toString() << "while:" << dateTimeString;
}

/*!
 * Returns true if this object and \a other are not the same.
 */
bool SDateTime::operator!=(const SDateTime &other) const {
    return !(mDay==other.mDay && mMonth==other.mMonth && mYear==other.mYear
             && mSecond==other.mSecond && mMinute==other.mMinute
             && mHour==other.mHour);
}

/*!
 * Returns true if this object is earlier than \a other.
 *
 * Method is optimised, it checks biggest time periods first and then narrows
 * down the comparison.
 */
bool SDateTime::operator<(const SDateTime &other) const {
    if (mYear < other.mYear) return true;
    if (mYear == other.mYear) {
        if (mMonth < other.mMonth) return true;
        if (mMonth == other.mMonth) {
            if (mDay < other.mDay) return true;
            if (mDay == other.mDay) {
                if (mHour < other.mHour) return true; // TODO: check with "00" vs. "12"
                if (mHour == other.mHour) {
                    if (mMinute < other.mMinute) return true;
                    if (mMinute == other.mMinute) {
                        if (mSecond < other.mSecond) return true;
                        else return false;
                    }
                }
            }
        }
    }

    return false;
}

/*!
 * Parses \a dateTime and returns corresponding SDateTime object. On error,
 * a valid date is returned! (1-1-1 0:0:0)
 *
 * \todo Add invalid/ null date concept.
 */
SDateTime SDateTime::fromString(const QByteArray &dateTime)
{
    return SDateTime(dateTime);
}

/*!
 * Parses \a dateTime and returns corresponding SDateTime object. On error,
 * a valid date is returned! (1-1-1 0:0:0)
 *
 * \todo Add invalid/ null date concept.
 */
SDateTime SDateTime::fromString(const QString &dateTime)
{
    return SDateTime(dateTime);
}

/*!
 * Returns a string representation of current date, in format: yyyy-MM-dd hh:mm:ss.
 */
QString SDateTime::toString() const
{
    return mStringRepresentation;
}

uint SDateTime::day() const
{
    return mDay;
}

uint SDateTime::month() const
{
    return mMonth;
}

int SDateTime::year() const
{
    return mYear;
}

uint SDateTime::second() const
{
    return mSecond;
}

uint SDateTime::minute() const
{
    return mMinute;
}

uint SDateTime::hour() const
{
    return mHour;
}

void SDateTime::setDay(const uint day)
{
    mDay = day;
    updateStringRepresentation();
}

void SDateTime::setMonth(const uint month)
{
    mMonth = month;
    updateStringRepresentation();
}

void SDateTime::setYear(const int year)
{
    mYear = year;
    updateStringRepresentation();
}

void SDateTime::setSecond(const uint second)
{
    mSecond = second;
    updateStringRepresentation();
}

void SDateTime::setMinute(const uint minute)
{
    mMinute = minute;
    updateStringRepresentation();
}

void SDateTime::setHour(const uint hour)
{
    mHour = hour;
    updateStringRepresentation();
}

void SDateTime::updateStringRepresentation()
{
    mStringRepresentation = QByteArray::number(mYear) + Tags::dateSeparator
            + QByteArray::number(mMonth) + Tags::dateSeparator
            + QByteArray::number(mDay)
            + QByteArrayLiteral(" ")
            + QByteArray::number(mHour) + Tags::timeSeparator
            + QByteArray::number(mMinute) + Tags::timeSeparator
            + QByteArray::number(mSecond);
}
