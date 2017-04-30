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
    QString mDate1 = "2017-04-30 13:06:59";
};

void SDateTimeTest::testStringOperators()
{
    SDateTime dt1 = SDateTime::fromString(mDate1);
    QVERIFY(dt1.day == 30);
    QVERIFY(dt1.month == 04);
    QVERIFY(dt1.year == 2017);
    QVERIFY(dt1.hour == 13);
    QVERIFY(dt1.minute == 6);
    QVERIFY(dt1.second == 59);
    qDebug() << dt1.toString(); // TODO: decide how to resolve this (output is "2017-4-30 13:6:59")
    QVERIFY(dt1.toString() == mDate1);
}

void SDateTimeTest::testOperators()
{
    SDateTime dt1(mDate1), dt2("2017-05-01 08:11:05");

    QVERIFY(dt1 != dt2);
    QVERIFY(dt1 < dt2);
}

QTEST_MAIN(SDateTimeTest)

#include "tst_sdatetime.moc"
