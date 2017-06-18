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
        const quint64 key(obj.keys().first().toULongLong(&ok));

        if (!ok) {
            qDebug() << "ERROR: could not read Tag key" << obj;
            return;
        }

        const QString value(obj.value(obj.keys().first()).toString());
        mTags.insert(key, value);
        mId++;
    }
}

QString SObjectTags::tag(const quint64 id) const
{
    return mTags.value(id);
}

quint64 SObjectTags::id(const QString &tag) const
{
    return mTags.key(tag);
}

bool SObjectTags::addTag(const QString &tag)
{
    if (mTags.key(tag) != 0) {
        qDebug() << "Tag alread exists" << mTags.key(tag) << tag;
        return false;
    }

    mId++;
    mTags.insert(mId, tag);
    return true;
}
