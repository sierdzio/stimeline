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
    //qDebug(sdatetime) << "Empty SDateTime";
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

    year = dateDivided.at(0).toInt();
    month = dateDivided.at(1).toUInt();
    day = dateDivided.at(2).toUInt();

    // Time
    const QStringList timeDivided(time.split(Tags::timeSeparator,
                                             QString::KeepEmptyParts,
                                             Qt::CaseSensitive));
    if (timeDivided.length() != 3) {
        qCDebug(sdatetime) << "Time parsing error!" << timeDivided;
        return;
    }

    hour = timeDivided.at(0).toUInt();
    minute = timeDivided.at(1).toUInt();
    second = timeDivided.at(2).toUInt();
    //qCDebug(sdatetime) << "Date parsed!" << toString() << "while:" << dateTimeString;
}

/*!
 * Returns true if this object and \a other are not the same.
 */
bool SDateTime::operator!=(const SDateTime &other) const {
    return !(day==other.day && month==other.month && year==other.year
             && second==other.second && minute==other.minute
             && hour==other.hour);
}

/*!
 * Returns true if this object is earlier than \a other.
 *
 * Method is optimised, it checks biggest time periods first and then narrows
 * down the comparison.
 */
bool SDateTime::operator<(const SDateTime &other) const {
    if (year < other.year) return true;
    if (year == other.year) {
        if (month < other.month) return true;
        if (month == other.month) {
            if (day < other.day) return true;
            if (day == other.day) {
                if (hour < other.hour) return true; // TODO: check with "00" vs. "12"
                if (hour == other.hour) {
                    if (minute < other.minute) return true;
                    if (minute == other.minute) {
                        if (second < other.second) return true;
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
 * a valid date is returned! (1-1-1 1:1:1)
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
    QString result;

    result = QString::number(year) + Tags::dateSeparator
            + QString::number(month) + Tags::dateSeparator
            + QString::number(day)
            + QStringLiteral(" ")
            + QString::number(hour) + Tags::timeSeparator
            + QString::number(minute) + Tags::timeSeparator
            + QString::number(second);

    return result;
}
