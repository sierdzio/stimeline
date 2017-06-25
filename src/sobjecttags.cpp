#include "sobjecttags.h"
#include "tags.h"

#include <QJsonValue>
#include <QJsonObject>
#include <QDebug>

SObjectTags::SObjectTags(QObject *parent) : QObject(parent)
{
}

QJsonArray SObjectTags::toJson() const
{
    QJsonArray result;

    for (auto it = mTags.constBegin(); it != mTags.constEnd(); ++it) {
        result.append(QJsonValue(QJsonObject({{QString::number(it.key()), it.value()}})));
    }

    return result;
}

void SObjectTags::fromJson(const QJsonArray &json)
{
    mTags.clear();
    for (const QJsonValue &i: json) {
        const QJsonObject obj(i.toObject());
        bool ok = false;
        const uint key(obj.keys().first().toUInt(&ok));

        if (!ok) {
            qDebug() << "ERROR: could not read Tag key" << obj;
            return;
        }

        const QString value(obj.value(obj.keys().first()).toString());
        mTags.insert(key, value);
    }
}

void SObjectTags::clear()
{
    mTags.clear();
}

QString SObjectTags::value(const uint id) const
{
    return mTags.value(id);
}

uint SObjectTags::key(const QString &tag) const
{
    return mTags.key(tag);
}

bool SObjectTags::addTag(const QString &tag)
{
    const QString aTag(tag.toLower()); // TODO: locale-aware toLower()!
    const uint id = qHash(aTag);

    if (mTags.contains(id)) {
        qDebug() << "Tag alread exists" << id << aTag;
        return false;
    }

    mTags.insert(id, aTag);
    return true;
}
