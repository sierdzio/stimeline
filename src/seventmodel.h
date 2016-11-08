#ifndef SEVENTMODEL_H
#define SEVENTMODEL_H

#include "seventdb.h"
#include "tags.h"

#include <QAbstractListModel>
#include <QByteArray>
#include <QHash>
#include <QVariant>
#include <QObject>

class QModelIndex;

class SEventModel : public QAbstractListModel, public SEventDB
{
    Q_OBJECT

public:
    explicit SEventModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual void fromJson(const QJsonArray &json) override;
};

#endif // SEVENTMODEL_H
