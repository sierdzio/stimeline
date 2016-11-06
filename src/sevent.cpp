#include "sevent.h"
#include "tags.h"

#include <QJsonValue>

#include <QLoggingCategory>
#include <QDebug>
Q_LOGGING_CATEGORY(sevent, "SEvent")

/*!
 * \class sEvent
 *
 * \brief Base class for all events in a timeline.
 *
 * Base class for all events. Events can be chained into Plots using their IDs
 * and parent-child hierarchy.
 */

SEvent::SEvent() : QObject(nullptr)
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

QJsonObject SEvent::toJson() const
{
    // NOTE: to speed up this method (and thus file saving), it is possible to
    // keep a QJsonObject as private member and update it on the fly.
    QJsonObject result;

    result.insert(Tags::id, QJsonValue(QLatin1String(mId)));
    result.insert(Tags::name, QJsonValue(mName));
    result.insert(Tags::description, QJsonValue(mDescription));
    result.insert(Tags::from, QJsonValue(mFrom.toString()));
    result.insert(Tags::to, QJsonValue(mTo.toString()));

    return result;
}

void SEvent::fromJson(const QJsonObject &json)
{
    mId = json.value(Tags::id).toString().toLatin1();
    mName = json.value(Tags::name).toString();
    mDescription = json.value(Tags::description).toString();
    mFrom.fromString(json.value(Tags::from).toString());
    mTo.fromString(json.value(Tags::to).toString());

    //qCDebug(sevent).noquote() << "Event loaded from JSON. Data:\n" << toString();
}
