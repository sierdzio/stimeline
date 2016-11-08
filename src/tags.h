#ifndef TAGS_H
#define TAGS_H

#include <QByteArray>

namespace Tags {
// Metadata:
static const QByteArray version("version");
static const QByteArray timestamp("timestamp");
static const QByteArray author("author");
// Events:
static const QByteArray id("id");
static const QByteArray events("Events");
static const QByteArray name("name");
static const QByteArray description("description");
// Calendar:
static const QByteArray calendar("Calendar");
static const QByteArray daysInWeek("daysInWeek");
static const QByteArray daysInYear("daysInYear");
static const QByteArray monthsInYear("monthsInYear");
static const QByteArray leapDayPerYear("leapDayPerYear");
static const QByteArray leapDayAddsToMonthNumber("leapDayAddsToMonthNumber");
static const QByteArray months("Months");
static const QByteArray secondsInMinute("secondsInMinute");
static const QByteArray minutesInHour("minutesInHour");
static const QByteArray hoursInDay("hoursInDay");
// DateTime
static const QByteArray from("from");
static const QByteArray to("to");
// Settings
static const QByteArray autoLoadLastFile("autoLoadLastFile");
static const QByteArray lastOpenFilePath("lastOpenFilePath");
static const QByteArray lastSaveFilePath("lastSaveFilePath");
// Misc
static const QByteArray dateSeparator("-");
static const QByteArray timeSeparator(":");
}

#endif // TAGS_H
