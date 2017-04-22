#include <QtTest>
#include <QCoreApplication>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>

#include "sobject.h"
#include "sdatetime.h"
#include "tags.h"

class SObjectTest : public QObject
{
    Q_OBJECT

public:
    SObjectTest();
    ~SObjectTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testDefaults();
    void testConversions();
    void testJson();
};

SObjectTest::SObjectTest()
{
}

SObjectTest::~SObjectTest()
{
}

void SObjectTest::initTestCase()
{
}

void SObjectTest::cleanupTestCase()
{
}

void SObjectTest::testDefaults()
{
    SObject object;
    QVERIFY(!object.mId.isEmpty());
    QVERIFY(object.mType == SObject::ObjectType::None);
    QVERIFY(object.mName.isEmpty());
    QVERIFY(object.mPicturePath.isEmpty());
    QVERIFY(object.mDescription.isEmpty());
    QVERIFY(object.mFrom.toString() == SDateTime().toString());
    QVERIFY(object.mTo.toString() == SDateTime().toString());
    QVERIFY(object.isValid());

    QJsonObject jobj = object.toJson();
    QVERIFY(jobj.value(Tags::id).toString().toLatin1() == object.mId);
    QVERIFY(jobj.value(Tags::type).toString() == SObject::typeToString(SObject::ObjectType::None));
    QVERIFY(jobj.value(Tags::name).toString().isEmpty());
    QVERIFY(jobj.value(Tags::picturePath).toString().isEmpty());
    QVERIFY(jobj.value(Tags::description).toString().isEmpty());
    QVERIFY(jobj.value(Tags::from).toString() == SDateTime().toString());
    QVERIFY(jobj.value(Tags::to).toString() == SDateTime().toString());
}

void SObjectTest::testConversions()
{
    QVERIFY(SObject::typeToString("0") == "None");
    QVERIFY(SObject::typeToString("5") == "Map");

    QVERIFY(SObject::typeToString(0) == "None");
    QVERIFY(SObject::typeToString(5) == "Map");

    QVERIFY(SObject::typeToString(SObject::ObjectType::None) == "None");
    QVERIFY(SObject::typeToString(SObject::ObjectType::Map) == "Map");

    QVERIFY(SObject::stringToType("None") == SObject::ObjectType::None);
    QVERIFY(SObject::stringToType("Map") == SObject::ObjectType::Map);
}

void SObjectTest::testJson()
{
    QFile file(":/testData/sobject1.json");
    Q_ASSERT(file.open(QFile::Text | QFile::ReadOnly));

    QJsonParseError err;
    const QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &err);
    QVERIFY(!doc.isEmpty() && err.error == QJsonParseError::NoError);

    SObject obj(doc.object());
    QVERIFY(obj.isValid());
    QVERIFY(obj.mId == "1c462dec69dfc2ada12db5a02e4dceaf04b40ef6");
    QVERIFY(obj.mType == SObject::ObjectType::Event);
    QVERIFY(obj.mName == "Event 2");
    QVERIFY(obj.mPicturePath.isEmpty());
    QVERIFY(obj.mDescription == "BBB");
    QVERIFY(obj.mFrom.toString() == "1-1-3 1:1:4");
    QVERIFY(obj.mTo.toString() == "1-1-3 1:1:7");
}

QTEST_MAIN(SObjectTest)
#include "SObjectTest.moc"
