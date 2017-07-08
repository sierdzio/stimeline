#pragma once

#include <QHash>
#include <QString>
#include <QObject>
#include <QJsonArray>

class SObjectTags : public QObject
{
    Q_OBJECT

    struct Tag {
        QString value; // Tag value. This is displayed to users
        uint refCount = 0; // RefCount - how many times this tag is used
    };

public:
    explicit SObjectTags(QObject *parent = nullptr);

    QJsonArray toJson() const;
    void fromJson(const QJsonArray &json);

    void clear();

public slots:
    QString value(const uint key) const;
    uint addTag(const QString &value);
    void removeTag(const uint key);

private:
    QHash<uint, Tag> mTags;
};
