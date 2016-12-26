#include "sperson.h"
#include "tags.h"
#include "sutils.h"

SPerson::SPerson()
{
    mId = SUtils::generateId();
}

SPerson::SPerson(const QJsonObject &from)
{
    fromJson(from);
}

QJsonObject SPerson::toJson() const
{
    QJsonObject result;

    result.insert(Tags::id, QJsonValue(QLatin1String(mId)));
    result.insert(Tags::picturePath, QJsonValue(QLatin1String(mPicturePath)));
    result.insert(Tags::name, QJsonValue(mName));
    result.insert(Tags::description, QJsonValue(mDescription));

    return result;
}

void SPerson::fromJson(const QJsonObject &json)
{
    mId = json.value(Tags::id).toString().toLatin1();
    mPicturePath = json.value(Tags::picturePath).toString().toLatin1();
    mName = json.value(Tags::name).toString();
    mDescription = json.value(Tags::description).toString();

    //qCDebug(sevent).noquote() << "Event loaded from JSON. Data:\n" << toString();
}
