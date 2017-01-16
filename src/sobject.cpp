#include "sobject.h"
#include "tags.h"
#include "sassistant.h"

#include <QMetaEnum>
#include <QJsonValue>
#include <QDebug>
Q_LOGGING_CATEGORY(sevent, "SEvent")

/*!
 * \class SObject
 *
 * \brief Base class for all events in a timeline and other objects.
 *
 * Base class for all objects. An object can be:
 * \li an event
 * \li a person
 * \li an artifact
 * \li a place
 * \li a map
 */

/*!
 * Default constructor. It will automatically generate a random ID for the SEvent
 * if \a option is set to SEvent::InitialiseId.
 */
SObject::SObject(SObject::InitialisationOption option, ObjectType type)
    : mType(type)
{
    if (option == InitialisationOption::InitialiseId) {
        mId = SAssistant::generateId();
    }
}

SObject::SObject(const QJsonObject &from)
{
    fromJson(from);
}

QByteArray SObject::id() const
{
    return mId;
}

bool SObject::isValid() const
{
    if (mId.isEmpty()) {
        return false;
    }

    return true;
}

QJsonObject SObject::toJson() const
{
    // NOTE: to speed up this method (and thus file saving), it is possible to
    // keep a QJsonObject as private member and update it on the fly.
    QJsonObject result;

    result.insert(Tags::id, QJsonValue(QLatin1String(mId)));
    result.insert(Tags::type, typeToString(mType));
    result.insert(Tags::name, QJsonValue(mName));
    result.insert(Tags::picturePath, QJsonValue(mPicturePath));
    result.insert(Tags::description, QJsonValue(mDescription));
    result.insert(Tags::from, QJsonValue(mFrom.toString()));
    result.insert(Tags::to, QJsonValue(mTo.toString()));

    return result;
}

void SObject::fromJson(const QJsonObject &json)
{
    mId = json.value(Tags::id).toString().toLatin1();
    mType = stringToType(json.value(Tags::type).toString());
    mName = json.value(Tags::name).toString();
    mPicturePath = json.value(Tags::picturePath).toString();
    mDescription = json.value(Tags::description).toString();
    mFrom = SDateTime::fromString(json.value(Tags::from).toString());
    mTo = SDateTime::fromString(json.value(Tags::to).toString());

    //qCDebug(sevent).noquote() << "Event loaded from JSON. Data:\n" << toString();
}

/*!
 * Returns type name for given type number (QML often passes numbers as strings).
 */
QString SObject::typeToString(const QString &type)
{
    bool isNumber = false;
    const int number = type.toInt(&isNumber);

    if (isNumber) {
        return typeToString(number);
    }

    return type;
}

QString SObject::typeToString(const int type)
{
    return typeToString(SObject::ObjectType(type));
}

QString SObject::typeToString(const SObject::ObjectType type)
{
    return QMetaEnum::fromType<SObject::ObjectType>().valueToKey(int(type));
}

SObject::ObjectType SObject::stringToType(const QString &type)
{
    bool isNumber = false;
    const int number = type.toInt(&isNumber);

    if (isNumber) {
        return SObject::ObjectType(number);
    }

    return ObjectType(QMetaEnum::fromType<SObject::ObjectType>()
                      .keyToValue(type.toLatin1().constData()));
}
