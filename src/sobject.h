#pragma once

#include "sdatetime.h"

#include <QByteArray>
#include <QString>
#include <QJsonObject>
#include <QObject>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(sevent)

class SObjectModel;
class SEventSortProxyModel;

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

    friend class SObjectModel;
    friend class SEventSortProxyModel;

public:
    enum class InitialisationOption {
        InitialiseId,
        DoNotInitialiseId
    };

    enum class ObjectType {
        None = 0,
        Event,
        Person,
        Artifact,
        Place,
        Map
    }; Q_ENUM(ObjectType)

    SObject(InitialisationOption option = InitialisationOption::InitialiseId,
            ObjectType type = ObjectType::None);
    SObject(const QJsonObject &from);

    QByteArray id() const;
    bool isValid() const;

    QJsonObject toJson() const;
    void fromJson(const QJsonObject &json);

    static QString typeToString(const QString &type);
    static QString typeToString(const int type);
    static QString typeToString(const ObjectType type);
    static ObjectType stringToType(const QString &type);

private:
    QByteArray mId;
    ObjectType mType;
    QString mName;
    QString mPicturePath;
    QString mDescription;
    SDateTime mFrom;
    SDateTime mTo;
};
