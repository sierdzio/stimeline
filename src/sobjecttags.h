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

public slots:
    QString tag(const quint64 id) const;
    quint64 id(const QString &tag) const;
    bool addTag(const QString &tag);

private:
    QHash<quint64, QString> mTags;
    quint64 mId = 0;
};
