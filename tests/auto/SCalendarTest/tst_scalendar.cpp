#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <QFile>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "scalendar.h"
#include "sdatetime.h"
#include "tags.h"

class SCalendarTest : public QObject
{
    Q_OBJECT

public:
    SCalendarTest();

private Q_SLOTS:
    void testValidity();
    void testParsing();
    void testJsonOperators();
    void testCalendarTimeLogic();

private:
    void countSeconds(const SCalendar &cal, const QString &date, const quint64 shouldBe) const;

    QJsonArray mCalendarArray;
};

SCalendarTest::SCalendarTest()
{
    QFile file(":/testData/scalendar1.json");
    Q_ASSERT(file.open(QFile::Text | QFile::ReadOnly));

    QJsonParseError err;
    const QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &err);
    qDebug() << err.errorString();
    QVERIFY(!doc.isEmpty() && err.error == QJsonParseError::NoError);

    SCalendar cal;
    mCalendarArray = doc.object().value(Tags::calendar).toArray();
}

void SCalendarTest::testValidity()
{
    SCalendar cal;
    QVERIFY(cal.isValid());
}

void SCalendarTest::testParsing()
{
    SCalendar cal;
    cal.fromJson(mCalendarArray);
    QVERIFY(cal.isValid());

    QVERIFY(cal.mDaysInWeek == 7);
    QVERIFY(cal.mDaysInYear == 365);
    QVERIFY(cal.mDefaultDateTime == "2017-1-1 0:0:0");
    QVERIFY(cal.mHoursInDay == 24);
    QVERIFY(cal.mLeapDayAddsToMonthNumber == 2); // Hm, shouldn't it be 1? Zero-indexed
    QVERIFY(qFuzzyCompare(cal.mLeapDayPerYear, 0.2425));
    QVERIFY(cal.mMinutesInHour == 60);
    QVERIFY(cal.mMonthsInYear == uint(cal.mMonths.size()));
    QVERIFY(cal.mMonthsInYear == 12);
    QVERIFY(cal.mName == "Gregorian");
    QVERIFY(cal.mSecondsInMinute == 60);
}

void SCalendarTest::testJsonOperators()
{
    SCalendar cal;
    cal.fromJson(mCalendarArray);
    QVERIFY(cal.isValid());
    QVERIFY(cal.toJson() == mCalendarArray);

    QVERIFY(cal.daysInMonth(0) == 31);
    QVERIFY(cal.daysInMonth(1) == 28);
    QVERIFY(cal.monthName(0) == "January");
    QVERIFY(cal.monthName(11) == "December");
}

void SCalendarTest::testCalendarTimeLogic()
{
    SCalendar cal;
    cal.fromJson(mCalendarArray);
    QVERIFY(cal.isValid());
    const QString date1("2017-4-30 13:6:59");
    const QString date2("2017-04-30 13:06:51");
    QVERIFY(cal.isEarlier(date2, date1));
    QVERIFY(cal.duration(date2, date1) == 8);

    // For comparison, see https://www.timeanddate.com/date/durationresult.html?y1=0001&m1=01&d1=01&y2=2017&m2=04&d2=30&h1=0&i1=0&s1=0&h2=13&i2=06&s2=59
    countSeconds(cal, date1, 63629327219);
    countSeconds(cal, "1000-1-1 0:0:0", 31525977600);
    countSeconds(cal, "100-1-1 0:0:0", 3124137600);
    countSeconds(cal, "2-1-1 0:0:0", 31536000);
    countSeconds(cal, "1-2-1 0:0:0", 2678400);
    countSeconds(cal, "1-1-10 0:0:0", 777600);
    countSeconds(cal, "1-1-2 0:0:0", 86400);
    countSeconds(cal, "1-1-1 0:1:0", 60);
}

void SCalendarTest::countSeconds(const SCalendar &cal, const QString &date, const quint64 shouldBe) const
{
    const quint64 seconds = cal.secondsInDateTime(date);
    qDebug() << "Seconds in DT:" << seconds;
    qDebug() << "....Should be:" << shouldBe << "delta:" << qint64(seconds - shouldBe);
    //QVERIFY(seconds6 == 3124137600);
}

QTEST_MAIN(SCalendarTest)
#include "tst_scalendar.moc"
