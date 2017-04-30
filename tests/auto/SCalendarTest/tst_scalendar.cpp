#include <QString>
#include <QtTest>
#include <QCoreApplication>

#include "scalendar.h"
#include "sdatetime.h"

class SCalendarTest : public QObject
{
    Q_OBJECT

public:
    SCalendarTest();

private Q_SLOTS:
    void testValidity();
};

SCalendarTest::SCalendarTest()
{
}

void SCalendarTest::testValidity()
{
    SCalendar cal;
    QVERIFY(cal.isValid());
}

QTEST_MAIN(SCalendarTest)
#include "tst_scalendar.moc"
