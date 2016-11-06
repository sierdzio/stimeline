#ifndef SCALENDAR_H
#define SCALENDAR_H

#include <QString>
#include <QObject>
#include <QVector>
#include <QPair>
#include <QJsonObject>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(scalendar)

using SMonth = QPair<QString, int>;

class SCalendar
{
    Q_GADGET

public:
    SCalendar();
    bool isValid() const;

    QJsonArray toJson() const;
    void fromJson(const QJsonArray &json);

private:
    void checkValidity();

    bool mIsValid = false;

    QString mName = "Gregorian";
    // Date
    uint mDaysInWeek = 7;
    uint mDaysInYear = 365;
    uint mMonthsInYear = 12;
    qreal mLeapDayPerYear = 0.25;
    uint mLeapDayAddsToMonthNumber = 2;

    // Months
    QVector<SMonth> mMonths = {
        {"January", 31},
        {"February", 28},
        {"March", 31},
        {"April", 30},
        {"May", 31},
        {"June", 30},
        {"July", 31},
        {"August", 31},
        {"September", 30},
        {"October", 31},
        {"November", 30},
        {"December", 31}
    };

    // Time
    uint mSecondsInMinute = 60;
    uint mMinutesInHour = 60;
    uint mHoursInDay = 24;
};

#endif // SCALENDAR_H
