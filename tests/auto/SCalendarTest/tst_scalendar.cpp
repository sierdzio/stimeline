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

private Q_SLOTS:
    void testValidity();
    void testJsonOperators();
};

void SCalendarTest::testValidity()
{
    SCalendar cal;
    QVERIFY(cal.isValid());
}

void SCalendarTest::testJsonOperators()
{
    QFile file(":/testData/scalendar1.json");
    Q_ASSERT(file.open(QFile::Text | QFile::ReadOnly));

    QJsonParseError err;
    const QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &err);
    qDebug() << err.errorString();
    QVERIFY(!doc.isEmpty() && err.error == QJsonParseError::NoError);

    SCalendar cal;
    cal.fromJson(doc.object().value(Tags::calendar).toArray());
    QVERIFY(cal.isValid());
}

QTEST_MAIN(SCalendarTest)
#include "tst_scalendar.moc"
