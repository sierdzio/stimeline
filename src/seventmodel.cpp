#include "seventmodel.h"
#include "sevent.h"
#include "tags.h"

#include <QModelIndex>
#include <QJsonArray>
#include <QDebug>

Q_LOGGING_CATEGORY(seventmodel, "SEventModel")

SEventModel::SEventModel(QObject *parent) : QAbstractListModel(parent)
{
}

QHash<int, QByteArray> SEventModel::roleNames() const {
    QHash<int, QByteArray> roles;
    int i = Qt::UserRole + 1;
    roles[i++] = Tags::id;
    roles[i++] = Tags::name;
    roles[i++] = Tags::description;
    roles[i++] = Tags::from;
    roles[i++] = Tags::to;
    return roles;
}

int SEventModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mEvents.count();
}

QVariant SEventModel::data(const QModelIndex &index, int role) const
{
    const int row = index.row();
    const int roles = Qt::UserRole + 1;
    const SEvent event = mEvents.at(row);

    switch (role) {
    case roles: return event.mId;
    case roles+1: return event.mName;
    case roles+2: return event.mDescription;
    case roles+3: return event.mFrom.toString();
    case roles+4: return event.mTo.toString();
    default: return QVariant();
    }
}

QJsonArray SEventModel::toJson() const
{
    QJsonArray result;
    if (mEvents.isEmpty())
        return result;

    for (const SEvent &event: qAsConst(mEvents)) {
        result.append(event.toJson());
    }

    return result;
}

void SEventModel::fromJson(const QJsonArray &json)
{
    beginResetModel();

    if (mEvents.isEmpty() == false)
        mEvents.clear();

    for (const QJsonValue &event: json) {
        mEvents.append(SEvent(event.toObject()));
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
void SEventModel::addEvent(const QString &id, const QString &name,
                           const QString &description,
                           const QString &from, const QString &to)
{
    beginInsertRows(QModelIndex(), mEvents.size(), mEvents.size());
    auto event = SEvent(SEvent::InitialisationOption::DoNotInitialiseId);
    event.mId = id.toLatin1();
    event.mName = name;
    event.mDescription = description;
    if (!from.isEmpty()) event.mFrom = SDateTime::fromString(from);
    if (!to.isEmpty()) event.mTo = SDateTime::fromString(to);
    mEvents.append(event);
    endInsertRows();
}

void SEventModel::updateEvent(const QString &id, const QString &name,
                              const QString &description, const QString &from,
                              const QString &to)
{
    const int index = findEventIndex(id.toLatin1());

    // Event does not exist - create it instead
    if (index == -1) {
        addEvent(id, name, description, from, to);
        return;
    }

    const QModelIndex modelIndex(createIndex(index, 0));

    SEvent event;
    event.mId = id.toLatin1();
    event.mName = name;
    event.mDescription = description;
    event.mFrom = SDateTime::fromString(from);
    event.mTo = SDateTime::fromString(to);
    mEvents.replace(index, event);

    emit dataChanged(modelIndex, modelIndex);
}

void SEventModel::removeEvent(const QString &id)
{
    const int index = findEventIndex(id.toLatin1());

    if (index == -1) {
        qDebug(seventmodel) << "Can't remove event with ID:" << id
                            << "because it could not be found.";
        return;
    }

    beginRemoveRows(QModelIndex(), index, index);
    mEvents.remove(index);
    endRemoveRows();
}

/*!
 * Returns event index in mEvents vector, denoting location of event with \a id,
 * or -1 if no such event is found.
 */
int SEventModel::findEventIndex(const QByteArray &id) const
{
    int index = 0;
    for (const SEvent &e: qAsConst(mEvents)) {
        if (e.id() == id) {
            return index;
        }

        ++index;
    }

    qCDebug(seventmodel) << "Could not find event with ID:" << id
                         << "Event will not be updated";
    return -1;
}
