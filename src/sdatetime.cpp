#include "sdatetime.h"
#include "tags.h"

#include <QStringList>

#include <QLoggingCategory>
#include <QDebug>
Q_LOGGING_CATEGORY(sdatetime, "SDateTime")

SDateTime::SDateTime()
{

}

bool SDateTime::operator!=(const SDateTime &other) const {
    return !(day==other.day && month==other.month && year==other.year
             && second==other.second && minute==other.minute
             && hour==other.hour);
}

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

SDateTime SDateTime::fromString(const QString &dateTime)
{
    if (dateTime.isEmpty()) {
        //qDebug(sdatetime) << "DateTime is empty!";
        return SDateTime();
    }

    // "1234-12-24 11:11:11"
    const QStringList dateAndTime(dateTime.split(QLatin1String(" "),
                                                 QString::KeepEmptyParts,
                                                 Qt::CaseSensitive));

    if (dateAndTime.length() != 2) {
        qCDebug(sdatetime) << "DateTime parsing error!" << dateAndTime;
        return SDateTime();
    }

    const QString date(dateAndTime.first());
    const QString time(dateAndTime.at(1));

    // Date
    const QStringList dateDivided(date.split(Tags::dateSeparator,
                                             QString::KeepEmptyParts,
                                             Qt::CaseSensitive));
    if (dateDivided.length() != 3) {
        qCDebug(sdatetime) << "Date parsing error!" << dateDivided;
        return SDateTime();
    }

    SDateTime result;
    result.year = dateDivided.at(0).toInt();
    result.month = dateDivided.at(1).toUInt();
    result.day = dateDivided.at(2).toUInt();

    // Time
    const QStringList timeDivided(time.split(Tags::timeSeparator,
                                             QString::KeepEmptyParts,
                                             Qt::CaseSensitive));
    if (timeDivided.length() != 3) {
        qCDebug(sdatetime) << "Time parsing error!" << timeDivided;
        return SDateTime();
    }

    result.hour = timeDivided.at(0).toUInt();
    result.minute = timeDivided.at(1).toUInt();
    result.second = timeDivided.at(2).toUInt();
    return result;
}

QString SDateTime::toString() const
{
    QString result;

    result = QString::number(year) + Tags::dateSeparator
            + QString::number(month) + Tags::dateSeparator
            + QString::number(day)
            + QLatin1String(" ")
            + QString::number(hour) + Tags::timeSeparator
            + QString::number(minute) + Tags::timeSeparator
            + QString::number(second);

    return result;
}
