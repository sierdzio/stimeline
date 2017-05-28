#include <QString>
#include <QtTest>
#include <QCoreApplication>

#include "sdatetime.h"

class SDateTimeTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void testStringOperators();
    void testOperators();

private:
    const QString mDate1 = "2017-4-30 13:6:59";
};

void SDateTimeTest::testStringOperators()
{
    const SDateTime dt1 = SDateTime::fromString(mDate1);
    QVERIFY(dt1.day() == 30);
    QVERIFY(dt1.month() == 04);
    QVERIFY(dt1.year() == 2017);
    QVERIFY(dt1.hour() == 13);
    QVERIFY(dt1.minute() == 6);
    QVERIFY(dt1.second() == 59);
    qDebug() << "Date time string:" << mDate1 << "after conversion:" << dt1.toString();
    QVERIFY(dt1.toString() == mDate1);
}

void SDateTimeTest::testOperators()
{
    const SDateTime dt1(mDate1), dt2("2017-05-01 08:11:05");

    QVERIFY(dt1 != dt2);
    QVERIFY(dt1 < dt2);
}

QTEST_MAIN(SDateTimeTest)

#include "tst_sdatetime.moc"
