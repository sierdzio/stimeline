#include "seventdb.h"

#include "tags.h"
#include "sevent.h"

#include <QJsonObject>
#include <QJsonValue>

SEventDB::SEventDB()
{

}

/*!
 * Clear current list of events. SEvent objects will be auto-deleted
 * by QSharedPointer.
 */
void SEventDB::clear()
{
    mEvents.clear();
}

QJsonArray SEventDB::toJson() const
{
    QJsonArray result;
    if (mEvents.isEmpty())
        return result;

    for (const SEventPtr &event: qAsConst(mEvents)) {
        result.append(event->toJson());
    }

    return result;
}

void SEventDB::fromJson(const QJsonArray &json)
{
    if (mEvents.isEmpty() == false)
        clear();

    for (const QJsonValue &event: json) {
        mEvents.append(SEventPtr::create(event.toObject()));
    }
}
