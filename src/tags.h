#pragma once

#include <QByteArray>

/*!
 * Tags namespace holds all necessary fixed strings used in the application.
 *
 * This helps to avoid typos and hard to detect errors.
 */
namespace Tags {
// General:
static const QByteArray picturesDir("pictures");
static const QByteArray extensionCompressed("tmln");
static const QByteArray extensionUncompressed("json");
static const QByteArray docFolderName("sTimeline");
static const QByteArray settingsFileName("settings.ini");
// Metadata:
static const QByteArray version("version");
static const QByteArray timestamp("timestamp");
static const QByteArray author("author");
// Objects:
static const QByteArray sobject("sobject");
static const int        sobjectRole(Qt::UserRole + 1);
static const QByteArray id("id");
static const QByteArray type("type");
static const QByteArray name("name");
static const QByteArray description("description");
static const QByteArray picturePath("picturePath");
// Object types:
static const QByteArray events("Events");
static const QByteArray people("People");
static const QByteArray artifacts("Artifacts");
static const QByteArray places("Places");
static const QByteArray maps("Maps");
// Calendar:
static const QByteArray calendar("Calendar");
static const QByteArray defaultDateTime("defaultDateTime");
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
// Tags
static const QByteArray tags("tags");
//Plots
static const QByteArray plots("plots");
// Settings
static const QByteArray autoLoadLastFile("autoLoadLastFile");
static const QByteArray autoSaveOnExit("autoSaveOnExit");
static const QByteArray useSimpleFileDialog("useSimpleFileDialog");
static const QByteArray lastOpenFilePath("lastOpenFilePath");
// Misc
static const QByteArray dateSeparator("-");
static const QByteArray timeSeparator(":");
static const QByteArray tagSeparator(";");
}
