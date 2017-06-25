#include "sobjectmodel.h"
#include "sobject.h"
#include "tags.h"

#include <QModelIndex>
#include <QJsonArray>
#include <QDebug>

Q_LOGGING_CATEGORY(sobjectmodel, "SObjectModel")

/*!
 * \class SObjectModel
 *
 * Model representing a collection of SObjects to Qt's MVC system.
 */

/*!
 * \var SObjectModel::mObjects
 *
 * Holds all SObject instances.
 */

/*!
 * Default constructor using \a parent. Move along.
 */
SObjectModel::SObjectModel(QObject *parent) : QAbstractListModel(parent)
{
}

/*!
 * Returns a has containing role indices and names.
 */
QHash<int, QByteArray> SObjectModel::roleNames() const {
    QHash<int, QByteArray> roles;
    int i = Qt::UserRole + 1;
    roles[i++] = Tags::id;
    roles[i++] = Tags::type;
    roles[i++] = Tags::name;
    roles[i++] = Tags::picturePath;
    roles[i++] = Tags::description;
    roles[i++] = Tags::from;
    roles[i++] = Tags::to;
    return roles;
}

/*!
 * Returns the overal number of SObjects. \a parent is unused.
 */
int SObjectModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mObjects.count();
}

/*!
 * Returns SObject data for given \a index and \a role. \a role needs to match
 * one of roleNames().
 */
QVariant SObjectModel::data(const QModelIndex &index, int role) const
{
    const int row = index.row();
    const int roles = Qt::UserRole + 1;
    const SObject object = mObjects.at(row);

    switch (role) {
    case roles: return object.mId;
    case roles+1: return SObject::typeToString(object.mType);
    case roles+2: return object.mName;
    case roles+3: return object.mPicturePath;
    case roles+4: return object.mDescription;
    case roles+5: return object.mFrom.toString();
    case roles+6: return object.mTo.toString();
    default: return QVariant();
    }
}

bool SObjectModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, count);
    //mObjects.clear();
    mObjects.remove(row, count);
    endRemoveRows();

    return true;
}

void SObjectModel::clear()
{
    removeRows(0, mObjects.count(), QModelIndex());
}

/*!
 * Returns a JSON array containing all SObjects withing this model.
 */
QJsonArray SObjectModel::toJson() const
{
    QJsonArray result;
    if (mObjects.isEmpty())
        return result;

    for (const SObject &event: qAsConst(mObjects)) {
        result.append(event.toJson());
    }

    return result;
}

/*!
 * Populates the model with SObjects defined in \a json.
 */
void SObjectModel::fromJson(const QJsonArray &json)
{
    beginResetModel();

    if (mObjects.isEmpty() == false)
        mObjects.clear();

    for (const QJsonValue &event: json) {
        mObjects.append(SObject(event.toObject()));
    }

    endResetModel();
}

/*!
 * Adds a new event, filling it with data: \a name, \a description, \a from and
 * \a to and returns the ID of newly created event.
 *
 * \warning \a from and \a to should be replaced with datetime-aware objects
 * instead of QString.
 */
void SObjectModel::addObject(const QString &id, const QString &type,
                             const QString &name, const QString &picturePath,
                             const QString &description,
                             const QString &from, const QString &to)
{
    beginInsertRows(QModelIndex(), mObjects.size(), mObjects.size());
    auto typeEnum = SObject::stringToType(type);
    auto object = SObject(SObject::InitialisationOption::DoNotInitialiseId, typeEnum);
    object.mId = id.toLatin1();
    object.mName = name;
    object.mPicturePath = picturePath;
    object.mDescription = description;
    if (!from.isEmpty()) object.mFrom = SDateTime(from);
    if (!to.isEmpty()) object.mTo = SDateTime(to);
    mObjects.append(object);
    endInsertRows();
}

/*!
 * Updates a SObject recognised by \a id. All characteristics are updated:
 * \a type, \a name, \a picturePath, \a description, \a from and \a to.
 */
void SObjectModel::updateObject(const QString &id, const QString &type,
                                const QString &name, const QString &picturePath,
                                const QString &description, const QString &from,
                                const QString &to)
{
    qDebug() << "UPDATE:" << id << type << name;

    const int index = findObjectIndex(id.toLatin1());

    // Event does not exist - create it instead
    if (index == -1) {
        addObject(id, type, name, picturePath, description, from, to);
        return;
    }

    const QModelIndex modelIndex(createIndex(index, 0));
    auto typeEnum = SObject::stringToType(type);

    SObject object(SObject::InitialisationOption::DoNotInitialiseId, typeEnum);
    object.mId = id.toLatin1();
    object.mName = name;
    object.mPicturePath = picturePath;
    object.mDescription = description;
    object.mFrom = SDateTime(from);
    object.mTo = SDateTime(to);
    mObjects.replace(index, object);

    emit dataChanged(modelIndex, modelIndex);
}

/*!
 * Removes the object recognised by \a id.
 */
void SObjectModel::removeObject(const QString &id)
{
    const int index = findObjectIndex(id.toLatin1());

    if (index == -1) {
        qDebug(sobjectmodel) << "Can't remove object with ID:" << id
                             << "because it could not be found.";
        return;
    }

    beginRemoveRows(QModelIndex(), index, index);
    mObjects.remove(index);
    endRemoveRows();
}

void SObjectModel::updateObject(const SObject &obj)
{
    qDebug() << "UPDATE:" << obj.mId << obj.mType << obj.mName;

    const int index = findObjectIndex(obj.mId);

    // Event does not exist - create it instead
    if (index == -1) {
        //addObject(obj.mId, obj.mType, obj.mName, obj.picturePath, obj.description, obj.from, obj.to);
        return;
    }

    const QModelIndex modelIndex(createIndex(index, 0));
    mObjects.replace(index, obj);

    emit dataChanged(modelIndex, modelIndex);
}

SObject SObjectModel::object(const QString &id) const
{
    return mObjects.at(findObjectIndex(id.toLatin1()));
}

/*!
 * Returns event index in mEvents vector, denoting location of event with \a id,
 * or -1 if no such event is found.
 */
int SObjectModel::findObjectIndex(const QByteArray &id) const
{
    int index = 0;
    for (const SObject &e: qAsConst(mObjects)) {
        if (e.id() == id) {
            return index;
        }

        ++index;
    }

    return -1;
}
