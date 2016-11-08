#ifndef SEVENTMODEL_H
#define SEVENTMODEL_H

#include "tags.h"

#include <QAbstractListModel>
#include <QByteArray>
#include <QHash>
#include <QObject>
#include <QSharedPointer>

class SEventDB;

class SEventModel : public QAbstractListModel
{
    Q_OBJECT

public:

    explicit SEventModel(const QSharedPointer<SEventDB> &eventDb,
                         QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

private:
    QSharedPointer<SEventDB> mEventDb;
};

#endif // SEVENTMODEL_H
