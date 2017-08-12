#pragma once

#include "sdatetime.h"

#include <QVector>
#include <QVariantList>
#include <QByteArray>
#include <QString>
#include <QJsonObject>
#include <QObject>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(sevent)

class SObject;
struct SObjectIndex;

// Unfortunately, QML does not understant QVector :|
using TagContainer = QVector<uint>;
using SObjectContainer = QVector<SObject>;

class SObjectModel;
class SObjectSortProxyModel;

class SObject
{
    Q_GADGET

    Q_PROPERTY(QByteArray id MEMBER mId)
    Q_PROPERTY(ObjectType type MEMBER mType)
    Q_PROPERTY(QString name MEMBER mName)
    Q_PROPERTY(QString picturePath MEMBER mPicturePath)
    Q_PROPERTY(QString description MEMBER mDescription)
    Q_PROPERTY(SDateTime from MEMBER mFrom)
    Q_PROPERTY(SDateTime to MEMBER mTo)
    Q_PROPERTY(TagContainer tags MEMBER mTags)
    Q_PROPERTY(TagContainer plots MEMBER mPlots)
    //Q_PROPERTY(Plot chapter MEMBER mChapter)
    Q_PROPERTY(QByteArray era MEMBER mEra)

    /*! This property is for GUI selection. It is not saved into JSON. That is
     *  intentional!
     */
    Q_PROPERTY(bool selected MEMBER mSelected)

    friend class SObjectModel;
    friend class SObjectSortProxyModel;
    friend class SObjectTest;
    friend class STimeline;

public:
    enum class ObjectType {
        None = 0,
        Event,
        Person,
        Artifact,
        Place,
        Map
    };
    Q_ENUM(ObjectType)

    SObject(ObjectType type = ObjectType::None);
    SObject(const QJsonObject &from);

    QByteArray id() const; //!< K
    bool isValid() const;

    QJsonObject toJson() const;
    void fromJson(const QJsonObject &json);

    bool operator<(const SObject &other) const;
    bool operator>(const SObject &other) const;
    bool operator>=(const SObject &other) const;
    bool operator<=(const SObject &other) const;

    Q_INVOKABLE SObject me() const;
    Q_INVOKABLE int tagCount() const;
    Q_INVOKABLE uint tagIdAt(const int index) const;

    static QString typeToString(const QString &type);
    static QString typeToString(const int type);
    static QString typeToString(const ObjectType type);
    static ObjectType stringToType(const QString &type);
    static QString joinTags(const TagContainer &tags);
    static TagContainer splitTags(const QString &tags);

    // SObjectContainer searching
    static SObjectIndex takeObject(SObjectContainer &objects, const QByteArray &id);
    static SObjectIndex findObject(const SObjectContainer &objects, const QByteArray &id);
    static int findObjectIndex(const SObjectContainer &objects, const QByteArray &id);

private:
    QByteArray mId;
    QString mName;
    QString mPicturePath;
    QString mDescription;
    SDateTime mFrom;
    SDateTime mTo;
    TagContainer mTags;
    TagContainer mPlots;
    QByteArray mEra;
    ObjectType mType = ObjectType::None;

    bool mSelected = false;
};

struct SObjectIndex {
    int index = -1;
    SObject object;
};

Q_DECLARE_METATYPE(SObject*);
Q_DECLARE_METATYPE(TagContainer);
