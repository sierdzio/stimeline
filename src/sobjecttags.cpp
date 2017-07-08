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
        result.append(QJsonValue(QJsonObject({{QString::number(it.key()),
                                               it.value().value}})));
    }

    return result;
}

void SObjectTags::fromJson(const QJsonArray &json)
{
    mTags.clear();
    for (const QJsonValue &i: json) {
        const QJsonObject obj(i.toObject());
        const QString keyString(obj.keys().first());
        bool ok = false;

        // TODO: categorized logging!
        if (keyString.isEmpty()) {
            qDebug() << "Empty tag key. This is normal if no tags are set.";
            return;
        }

        const uint key(keyString.toUInt(&ok));

        if (!ok) {
            qDebug() << "ERROR: could not read Tag key" << obj;
            return;
        }

        const QString value(obj.value(obj.keys().first()).toString());
        mTags.insert(key, Tag{value, 0}); // refCount is populated later
        //qDebug() << "Reading tag:" << key << value;
    }
}

void SObjectTags::clear()
{
    mTags.clear();
}

QString SObjectTags::value(const uint id) const
{
    return mTags.value(id).value;
}

uint SObjectTags::addTag(const QString &tag)
{
    const QString aTag(tag.toLower()); // TODO: locale-aware toLower()!
    const uint id = qHash(aTag);

    Tag t = mTags.take(id);

    if (t.value.isEmpty())
        t.value = aTag;

    t.refCount++; // TODO: check refcounts after file loading!
    mTags.insert(id, t);
    return id;
}

void SObjectTags::removeTag(const uint key)
{
    if (!mTags.contains(key)) {
        qDebug() << "Tag not found!" << key;
        return;
    }

    Tag tag = mTags.take(key);
    if (tag.refCount == 1 || tag.refCount == 0)
        return;

    tag.refCount--;
    mTags.insert(key, tag);
}
