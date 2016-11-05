#include "sevent.h"
#include "tags.h"

#include <QJsonValue>
#include <QJsonArray>
#include <QJsonDocument>

#include <QLoggingCategory>
#include <QDebug>

/*!
 * \class sEvent
 *
 * \brief Base class for all events in a timeline.
 *
 * Base class for all events. Events can be chained into Plots using their IDs
 * and parent-child hierarchy.
 */

Q_LOGGING_CATEGORY(sevent, "SEvent")

SEvent::SEvent()
{
}

SEvent::SEvent(const QJsonObject &from)
{
    fromJson(from);
}

QByteArray SEvent::id() const
{
    return mId;
}

bool SEvent::isValid() const
{
    if (mId.isEmpty()) {
        return false;
    }

    return true;
}

bool SEvent::isRoot() const
{
    if (isValid() == false)
        return false;

    return mParentId.isEmpty();
}

SEventPtr SEvent::parent() const
{
    return mParent;
}

SEventVector SEvent::children() const
{
    return mChildren;
}

/*!
 * Returns parent event ID if present.
 *
 * This is useful when first constructing event hierarchy from JSON - we don't
 * have all objects created yet so parent() is not available, but parent's ID is
 * already known.
 *
 * \sa parent, fromJson, childrenIds
 */
QByteArray SEvent::parentId() const
{
    return mParentId;
}

/*!
 * Returns parent event ID if present.
 *
 * This is useful when first constructing event hierarchy from JSON - we don't
 * have all objects created yet so children() is empty, but children IDs are
 * already known.
 *
 * \sa children, fromJson, parentId
 */
QVector<QByteArray> SEvent::childrenIds() const
{
    return mChildrenIds;
}

QJsonObject SEvent::toJson() const
{
    // NOTE: to speed up this method (and thus file saving), it is possible to
    // keep a QJsonObject as private member and update it on the fly.
    QJsonObject result;

    result.insert(Tags::id, QJsonValue(QLatin1String(mId)));
    result.insert(Tags::parent, QJsonValue(QLatin1String(mParentId)));

//    QJsonArray children;
//    for (const QByteArray &value: qAsConst(mChildrenIds)) {
//        children += QJsonValue(QLatin1String(value));
//    }

//    result.insert(Tags::children, QJsonValue(children));
    result.insert(Tags::name, QJsonValue(mName));

    return result;
}

void SEvent::fromJson(const QJsonObject &json)
{
    // Clear previous values if any:
    mParent.clear();
    for (SEventPtr ptr: qAsConst(mChildren)) {
        ptr.clear();
    }

    mId = json.value(Tags::id).toString().toLatin1();
    mParentId = json.value(Tags::parent).toString().toLatin1();

//    const QJsonArray children = json.value(Tags::children).toArray();
//    for (const QJsonValue &value: children) {
//        mChildrenIds.append(value.toString().toLatin1());
//    }

    mName = json.value(Tags::name).toString();

    // TODO: temp, for testing only. Remove for production.
    qCDebug(sevent).noquote() << "Event loaded from JSON. Data:\n"
                              << toString();
}

QString SEvent::toString() const
{
    return QJsonDocument(toJson()).toJson();
}
