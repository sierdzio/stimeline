#include "seventdb.h"

#include "tags.h"
#include "sevent.h"

#include <QJsonValue>
#include <QDebug>

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

QJsonObject SEventDB::toJson() const
{
    QJsonObject result;
    if (mEvents.isEmpty())
        return result;

    for (const SEventPtr &event: qAsConst(mEvents)) {
        result.insert(Tags::event, event->toJson());
    }

    return result;
}

void SEventDB::fromJson(const QJsonObject &json)
{
    if (mEvents.isEmpty() == false)
        clear();

    qDebug() << "Events count:" << json.size();

    for (const QJsonValue &event: json) {
        mEvents.append(SEventPtr::create(event.toObject()));
    }
}
