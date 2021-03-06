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
 *
 * Every object, regardless of type, can have a name and description. Additionally,
 * a picture can be provided. Pictures are stored separate from JSON data and
 * referenced by a relative path.
 *
 * An object has a start date (from) and end date (to). They can be the same
 * (meaning the object will have no duration; it will be a point in time).
 */

/*!
 * \enum SObject::InitialisationOption
 *
 * SObject can be initialised with or without an ID. Please remember that in order
 * to be usable, the object has to have an id.
 */

/*!
 * \enum SObject::ObjectType
 *
 * Object type helps to determine what the given object is about. Also, different
 * SObjectModels store different types of objects.
 */

/*!
 * \property SObject::id
 *
 * Object ID. Should be unique.
 */

/*!
 * \property SObject::type
 *
 * Object type.
 */

/*!
 * \property SObject::name
 *
 * Object name.
 */

/*!
 * \property SObject::picturePath
 *
 * Relative path to the picture representing this object.
 */

/*!
 * \property SObject::description
 *
 * Object description.
 */

/*!
 * \property SObject::from
 *
 * Beginning date of this object/ event.
 */

/*!
 * \property SObject::to
 *
 * End date for this object/ event.
 */

/*!
 * \property SObject:tags
 *
 * Contains tags associated with the object. Tags make it easier to search,
 * filter and organize objects.
 */

/*!
 * \property SObject:plots
 *
 * Contains plots associated with the object. Plots are consistent packages
 * of objects, arranged in a particular order.
 */

/*!
 * Default constructor. It will automatically generate a random ID for the SEvent
 * if \a option is set to SEvent::InitialiseId.
 */
SObject::SObject(ObjectType type)
    : mId(SAssistant::generateId()), mType(type)
{
}

/*!
 * Constructs a new SObject \a from JSON data. Useful when loading from file.
 */
SObject::SObject(const QJsonObject &from)
{
    fromJson(from);
}

/*!
 * Returns object's ID.
 */
QByteArray SObject::id() const
{
    return mId;
}

/*!
 * Reutrns true if object is valid (has an id).
 */
bool SObject::isValid() const
{
    if (mId.isEmpty()) {
        return false;
    }

    return true;
}

/*!
 * Returns object's JSON representation.
 */
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
    result.insert(Tags::tags, QJsonValue(joinTags(mTags)));
    result.insert(Tags::plots, QJsonValue(joinTags(mPlots)));
    result.insert(Tags::eras, QJsonValue(QLatin1String(mEra)));

    return result;
}

/*!
 * Sets the object up based on \a json data.
 */
void SObject::fromJson(const QJsonObject &json)
{
    mId = json.value(Tags::id).toString().toLatin1();
    mType = stringToType(json.value(Tags::type).toString());
    mName = json.value(Tags::name).toString();
    mPicturePath = json.value(Tags::picturePath).toString();
    mDescription = json.value(Tags::description).toString();
    mFrom = SDateTime(json.value(Tags::from).toString());
    mTo = SDateTime(json.value(Tags::to).toString());
    mTags = splitTags(json.value(Tags::tags).toString());
    mPlots = splitTags(json.value(Tags::plots).toString());
    mEra = json.value(Tags::eras).toString().toLatin1();

    //qCDebug(sevent).noquote() << "Event loaded from JSON. Data:\n" << toString();
}

bool SObject::operator<(const SObject &other) const
{
    return mFrom < other.mFrom;
}

bool SObject::operator>(const SObject &other) const
{
    return mFrom > other.mFrom;
}

bool SObject::operator>=(const SObject &other) const
{
    return mFrom >= other.mFrom;
}

bool SObject::operator<=(const SObject &other) const
{
    return mFrom <= other.mFrom;
}

/*!
 * Returns this object. This method looks silly, I know, but the reason for its
 * existence is that this is the only way to interact with SObject directly
 * in QML.
 */
SObject SObject::me() const
{
    return *this;
}

int SObject::tagCount() const
{
    return mTags.count();
}

QByteArray SObject::tagIdAt(const int index) const
{
    return mTags.at(index);
}

int SObject::plotCount() const
{
    return mPlots.count();
}

QByteArray SObject::plotIdAt(const int index) const
{
    return mPlots.at(index);
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

/*!
 * Returns a string name of given \a type.
 */
QString SObject::typeToString(const int type)
{
    return typeToString(SObject::ObjectType(type));
}

/*!
 * Returns a string name of given \a type.
 */
QString SObject::typeToString(const SObject::ObjectType type)
{
    return QMetaEnum::fromType<SObject::ObjectType>().valueToKey(int(type));
}

/*!
 * Converts given \a type name to enum value.
 */
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

/*!
 * Returns all tag IDs in a single string. Used for saving into JSON.
 */
QString SObject::joinTags(const TagContainer &tags)
{
    QString result;

    for (const auto &value : tags) {
        if (!result.isEmpty())
            result += Tags::tagSeparator;

        if (!value.isEmpty())
            result += value;
    }

    return result;
}

/*!
 * Returns list of tags read from \a tags string. Used for reading from JSON.
 */
TagContainer SObject::splitTags(const QString &tags)
{
    const QStringList list(tags.split(Tags::tagSeparator));
    TagContainer result;

    for (const QString &value : list) {
        if (!value.isEmpty())
            result.append(value.toLatin1());
    }

    return result;
}

SObjectIndex SObject::takeObject(SObjectContainer &objects, const QByteArray &id)
{
    SObjectIndex index;
    index.index = findObjectIndex(objects, id);
    index.object = objects.takeAt(index.index);
    return index;
}

SObjectIndex SObject::findObject(const SObjectContainer &objects, const QByteArray &id)
{
    SObjectIndex index;
    index.index = findObjectIndex(objects, id);
    index.object = objects.at(index.index);
    return index;
}

/*!
 * Returns object index in \a objects vector, denoting location of object with \a id,
 * or -1 if no such object is found.
 */
int SObject::findObjectIndex(const SObjectContainer &objects, const QByteArray &id)
{
    int index = 0;
    for (const auto &e: objects) {
        if (e.id() == id) {
            return index;
        }

        ++index;
    }

    return -1;
}
