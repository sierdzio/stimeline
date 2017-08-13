#pragma once

#include <QHash>
#include <QString>
#include <QObject>
#include <QJsonArray>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(stagsmodel)

class STagsModel : public QObject
{
    Q_OBJECT

    struct Tag {
        QString value; // Tag value. This is displayed to users
        uint refCount = 0; // RefCount - how many times this tag is used
    };

public:
    explicit STagsModel(QObject *parent = nullptr);

    QJsonArray toJson() const;
    void fromJson(const QJsonArray &json);

    void clear();

public slots:
    QString value(const QByteArray &key) const;
    QByteArray addTag(const QByteArray &value);
    void removeTag(const QByteArray &key);

private:
    QHash<QByteArray, Tag> mTags;
};
