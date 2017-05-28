#pragma once

#include "sobject.h"

#include <QAbstractListModel>
#include <QByteArray>
#include <QHash>
#include <QVector>
#include <QVariant>
#include <QObject>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(sobjectmodel)

class QModelIndex;

class SObjectModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit SObjectModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    bool removeRows(int row, int count, const QModelIndex &parent) override;

    void clear();
    QJsonArray toJson() const;
    void fromJson(const QJsonArray &json);

public slots:
    void addObject(const QString &id,
                   const QString &type,
                   const QString &name,
                   const QString &picturePath,
                   const QString &description,
                   const QString &from,
                   const QString &to);
    void updateObject(const QString &id,
                      const QString &type,
                      const QString &name,
                      const QString &picturePath,
                      const QString &description,
                      const QString &from,
                      const QString &to);
    void removeObject(const QString &id);

protected:
    int findObjectIndex(const QByteArray &id) const;

    QVector<SObject> mObjects;
};
