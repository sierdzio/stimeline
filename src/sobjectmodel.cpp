#include "sobjectmodel.h"
#include "serasmodel.h"
#include "splotsmodel.h"
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
SObjectModel::SObjectModel(QObject *parent) : QAbstractListModel(parent),
    mRoleNames({
{Tags::sobjectRole, Tags::sobject},
{Tags::selectedRole, Tags::selected},
{Tags::selectedCountRole, Tags::selectedCount},
{Tags::eraRole, Tags::era}
               })
{
}

/*!
 * Returns a has containing role indices and names.
 */
QHash<int, QByteArray> SObjectModel::roleNames() const {
    return mRoleNames;
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
    const auto row = index.row();
    const auto roleName = mRoleNames.value(role);

    if (roleName == Tags::sobject)
        return QVariant::fromValue(mObjects.at(row));
    else if (roleName == Tags::selected)
        return mObjects.at(row).mSelected;
    else if (roleName == Tags::selectedCount)
        return mSelected.size();
    else if (roleName == Tags::era)
        return mObjects.at(row).mEra;

    return QVariant();
}

bool SObjectModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    const auto row = index.row();
    const auto roleName = mRoleNames.value(role);

    // Handle item selection
    if (roleName == Tags::selected) {
        auto obj = mObjects.at(row);
        const auto selected = value.toBool();
        if (obj.mSelected != selected) {
            obj.mSelected = selected;
            if (selected) mSelected.append(obj.mId);
            else mSelected.removeOne(obj.mId);

            mObjects.replace(row, obj);
            emit dataChanged(index, index);
        }
        //qDebug(sobjectmodel) << "Selected count:" << mSelectedCount;
        return true;
    }

    return false;
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

void SObjectModel::setErasModel(SErasModel *model)
{
    mErasModel = model;
}

/*!
 * Sets the SEra \a id for all objects which begin after (and including) \a from
 * SObject, and before (including) \a to SObject. To determine when a SObject
 * begins, we take SObject::from value.
 *
 * \a id is SEra id.
 * \a from is SObject id.
 * \a to is SObject id.
 */
void SObjectModel::setEra(const QByteArray &id, const QByteArray &from,
                          const QByteArray &to)
{
    // TODO: can we do it in single pass?
    const int fromObjectIndex = SObject::findObjectIndex(mObjects, from);
    const int toObjectIndex = SObject::findObjectIndex(mObjects, to);
    const SDateTime &fromDate = mObjects.at(fromObjectIndex).mFrom;
    const SDateTime &toDate = mObjects.at(toObjectIndex).mTo;

    // We will modify SObjects, so we can't use const iterator!
    for (auto it = mObjects.begin(); it < mObjects.end(); ++it) {
        const SDateTime &date = it->mFrom;
        if (date >= fromDate && date <= toDate) {
            it->mEra = id;
        }
    }
}

/*!
 * Adds a new event, filling it with data: \a name, \a description, \a from and
 * \a to and returns the ID of newly created event.
 *
 * \warning \a from and \a to should be replaced with datetime-aware objects
 * instead of QString.
 */
void SObjectModel::addObject(const SObject &obj)
{
    qDebug() << "ADD:" << obj.mId << obj.mType << obj.mName;

    beginInsertRows(QModelIndex(), mObjects.size(), mObjects.size());
    mObjects.append(obj);
    endInsertRows();
}

/*!
 * Removes the object recognised by \a id.
 */
void SObjectModel::removeObject(const QByteArray &id)
{
    qDebug() << "REMOVE:" << id;
    const int index = SObject::findObjectIndex(mObjects, id);

    if (index == -1) {
        qDebug(sobjectmodel) << "Can't remove object with ID:" << id
                             << "because it could not be found.";
        return;
    }

    beginRemoveRows(QModelIndex(), index, index);
    mObjects.remove(index);
    endRemoveRows();
}

void SObjectModel::removeSelectedObjects()
{
    const QVector<QByteArray> selected(mSelected);
    mSelected.clear();
    for (const auto &id : selected) {
        removeObject(id);
    }
}

void SObjectModel::updateObject(const SObject &obj)
{
    qDebug() << "UPDATE:" << obj.mId << obj.mType << obj.mName;

    const int index = SObject::findObjectIndex(mObjects, obj.mId);

    // Event does not exist - create it instead
    if (index == -1) {
        addObject(obj);
        return;
    }

    const QModelIndex modelIndex(createIndex(index, 0));
    mObjects.replace(index, obj);

    emit dataChanged(modelIndex, modelIndex);
}

/*!
 * Creates a new Era called \a name. All objects between first and last selected
 * (chronologically by "from" date and time) are assogmed to the new Era.
 *
 * This is shown in SObjectListPage by means of a new section in the ListView.
 */
void SObjectModel::createEraFromSelection(const QString &name)
{
    if (!mErasModel) {
        qDebug(sobjectmodel) << "Cannot create an Era when era model is not available";
        return;
    }

    SObjectContainer selectedObjects;
    for (const auto &id : qAsConst(mSelected)) {
        SObjectIndex index = SObject::findObject(mObjects, id);
        selectedObjects.append(index.object);
        // TODO: Consider switching to pointers to Sobjects instead of making
        // copies all the time.
    }

    // dataChanged() will be emitted later.
    mSelected.clear();

    // sort selectedObjects based on "from" date
    std::sort(selectedObjects.begin(), selectedObjects.end());
    const SObject &first = selectedObjects.first();
    const SObject &last = selectedObjects.last();
    const QByteArray eraId = mErasModel->insert(name, first.mId, last.mId);

    for (int i = 0; i < mObjects.size(); ++i) {
        const SObject &object = mObjects.at(i);
        if (object >= first && object <= last) {
            if (object.mEra != eraId) {
                SObject toReplace = object;
                toReplace.mEra = eraId;
                toReplace.mSelected = false;
                const QModelIndex midx(createIndex(i, 0));
                mObjects.replace(i, toReplace);
                emit dataChanged(midx, midx);
            }
        }
    }

    // TODO: add cleaning of existing eras
}

/*!
 * Creates a new Plot called \a name. Events in the plot are set in the same
 * order as user selected the SObjects.
 */
void SObjectModel::createPlotFromSelection(const QString &name, const QString &description)
{
    Q_UNUSED(description);

    if (!mPlotsModel) {
        qDebug(sobjectmodel) << "Cannot create a Plot when plot model is not available";
        return;
    }

    const QVector<QByteArray> selected(mSelected);
    const QByteArray id(mPlotsModel->insert(mSelected, name));
    mSelected.clear();

    for (int i = 0; i < mObjects.size(); ++i) {
        const SObject &object = mObjects.at(i);
        if (selected.contains(object.mId)) {
            if (!object.mPlots.contains(id)) {
                SObject toReplace = object;
                toReplace.mPlots.append(id);
                toReplace.mSelected = false;
                const QModelIndex midx(createIndex(i, 0));
                mObjects.replace(i, toReplace);
                emit dataChanged(midx, midx);
            }
        }
    }
}
