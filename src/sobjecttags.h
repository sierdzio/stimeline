#pragma once

#include <QHash>
#include <QObject>
#include <QJsonArray>

class SObjectTags : public QObject
{
    Q_OBJECT

public:
    explicit SObjectTags(QObject *parent = nullptr);

    QJsonArray toJson() const;
    void fromJson(const QJsonArray &json);

    void clear();

public slots:
    QString value(const uint key) const;
    uint key(const QString &value) const;
    bool addTag(const QString &value);

private:
    QHash<uint, QString> mTags;
};
