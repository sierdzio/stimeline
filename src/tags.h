#ifndef TAGS_H
#define TAGS_H

#include <QLatin1String>

namespace Tags {
// Metadata:
static const QLatin1String version("version");
static const QLatin1String timestamp("timestamp");
static const QLatin1String author("author");
// Events:
static const QLatin1String id("id");
static const QLatin1String events("Events");
static const QLatin1String name("name");
static const QLatin1String description("description");
// Calendar:
static const QLatin1String calendar("Calendar");
static const QLatin1String daysInWeek("daysInWeek");
static const QLatin1String daysInYear("daysInYear");
static const QLatin1String monthsInYear("monthsInYear");
static const QLatin1String leapDayPerYear("leapDayPerYear");
static const QLatin1String leapDayAddsToMonthNumber("leapDayAddsToMonthNumber");
static const QLatin1String months("Months");
static const QLatin1String secondsInMinute("secondsInMinute");
static const QLatin1String minutesInHour("minutesInHour");
static const QLatin1String hoursInDay("hoursInDay");
// DateTime
static const QLatin1String from("from");
static const QLatin1String to("to");
// Misc
static const QLatin1String dateSeparator("-");
static const QLatin1String timeSeparator(":");
}

#endif // TAGS_H
