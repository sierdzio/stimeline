#include <QtTest>
#include <QCoreApplication>

#include "sobject.h"
#include "sdatetime.h"

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
    Q_ASSERT(!object.mId.isEmpty());
    Q_ASSERT(object.mType == SObject::ObjectType::None);
    Q_ASSERT(object.mName.isEmpty());
    Q_ASSERT(object.mPicturePath.isEmpty());
    Q_ASSERT(object.mDescription.isEmpty());
    Q_ASSERT(object.mFrom.toString() == SDateTime().toString());
    Q_ASSERT(object.mTo.toString() == SDateTime().toString());
}

QTEST_MAIN(SObjectTest)
#include "SObjectTest.moc"
