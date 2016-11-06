#include "sdatetime.h"
#include "tags.h"

#include <QStringList>

#include <QLoggingCategory>
#include <QDebug>
Q_LOGGING_CATEGORY(sdatetime, "SDateTime")

SDateTime::SDateTime()
{

}

void SDateTime::fromString(const QString &dateTime)
{
    // "1234-12-24 11:11:11"
    const QStringList dateAndTime(dateTime.split(QLatin1String(" "),
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
