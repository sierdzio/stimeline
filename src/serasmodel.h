#pragma once

#include <QHash>
#include <QObject>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(serasmodel)

class SObjectModel;

class SErasModel : public QObject
{
    Q_OBJECT

public:
    struct SEra {
        QByteArray id;
        QString name;
        QByteArray from; // ID of first event
        QByteArray to; // ID of last event
    };

    explicit SErasModel(QObject *parent = nullptr);
    void clear();

    QJsonArray toJson() const;
    void fromJson(const QJsonArray &json);

    void applyTo(const QByteArray &id, SObjectModel *model);

public slots:
    QString name(const QByteArray &id) const;
    void insert(const QString &name, const QByteArray &from, const QByteArray &to);
    void remove(const QByteArray &id);

private:
    QHash<QByteArray, SEra> mEras;
};
