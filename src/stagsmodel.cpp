#include "stagsmodel.h"
#include "tags.h"

#include <QCryptographicHash>
#include <QJsonValue>
#include <QJsonObject>
#include <QDebug>

Q_LOGGING_CATEGORY(stagsmodel, "STagsModel")

/*!
 * \class STagsModel
 * \brief Main tags storage and translation class.
 *
 * The purpose of STagsModel is to be the "dictionary" for SObject's tags.
 * While SObject class stores only tag IDs (essentially a qHash over tag value),
 * this class provides the strings that these IDs represent.
 *
 * Additionally, with toJson() and fromJson(), tag data can be saved to and from
 * sTimeline JSON file.
 *
 * \note While there is "Model" in this class name, it is not derived from
 * QAbstractItemModel. It won't work as model for QML MVC components.
 */

STagsModel::STagsModel(QObject *parent) : QObject(parent)
{
}

QJsonArray STagsModel::toJson() const
{
    QJsonArray result;

    for (auto it = mTags.constBegin(); it != mTags.constEnd(); ++it) {
        result.append(QJsonValue(QJsonObject({{it.key(),
                                               it.value().value}})));
    }

    return result;
}

void STagsModel::fromJson(const QJsonArray &json)
{
    mTags.clear();
    for (const QJsonValue &i: json) {
        const QJsonObject obj(i.toObject());
        const QString keyString(obj.keys().first());

        if (keyString.isEmpty()) {
            qCDebug(stagsmodel) << "Empty tag key. This is normal if no tags are set.";
            return;
        }

        const QByteArray key(keyString.toLatin1());
        const QString value(obj.value(obj.keys().first()).toString());
        Tag tag;
        tag.value = value;
        mTags.insert(key, tag); // refCount is populated later
    }
}

void STagsModel::clear()
{
    mTags.clear();
}

QString STagsModel::value(const QByteArray &id) const
{
    return mTags.value(id).value;
}

QByteArray STagsModel::addTag(const QByteArray &tag)
{
    const QByteArray aTag(tag.toLower()); // TODO: locale-aware toLower()!
    const QByteArray id(QCryptographicHash::hash(aTag, QCryptographicHash::Md5));

    Tag t = mTags.take(id);

    if (t.value.isEmpty())
        t.value = aTag;

    t.refCount++; // TODO: check refcounts after file loading!
    mTags.insert(id, t);
    return id;
}

void STagsModel::removeTag(const QByteArray &key)
{
    if (!mTags.contains(key)) {
        qDebug(stagsmodel) << "Tag not found!" << key;
        return;
    }

    Tag tag = mTags.take(key);
    if (tag.refCount == 1 || tag.refCount == 0)
        return;

    tag.refCount--;
    mTags.insert(key, tag);
}
