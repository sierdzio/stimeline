#include "scalendar.h"
#include "tags.h"

#include <QJsonValue>
#include <QJsonArray>

#include <QLoggingCategory>
#include <QDebug>
Q_LOGGING_CATEGORY(scalendar, "SCalendar")

SCalendar::SCalendar()
{
    qCDebug(scalendar) << "Initializing default (Gregorian) calendar";
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
        months.append(QJsonValue(QJsonObject({{month.first, month.second}})));
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
        const SMonth month(key, monthObj.value(key).toInt());
        mMonths.append(month);
    }
    // Time
    mSecondsInMinute = uint(obj.value(Tags::secondsInMinute).toInt());
    mMinutesInHour = uint(obj.value(Tags::minutesInHour).toInt());
    mHoursInDay = uint(obj.value(Tags::hoursInDay).toInt());

    qCDebug(scalendar()) << mName << "calendar loaded";
}

