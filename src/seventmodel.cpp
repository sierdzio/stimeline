#include "seventmodel.h"
#include "seventdb.h"
#include "sevent.h"

#include <QModelIndex>

SEventModel::SEventModel(QObject *parent) : QAbstractListModel(parent)
{
}

QHash<int, QByteArray> SEventModel::roleNames() const {
    QHash<int, QByteArray> roles;
    int i = Qt::UserRole + 1;
    roles[i++] = Tags::id;
    roles[i++] = Tags::name;
    roles[i++] = Tags::description;
    roles[i++] = Tags::from;
    roles[i++] = Tags::to;
    return roles;
}

int SEventModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mEvents.count();
}

QVariant SEventModel::data(const QModelIndex &index, int role) const
{
    const int row = index.row();
    const int roles = Qt::UserRole + 1;
    const SEvent *event = mEvents.at(row).data();

    switch (role) {
    case roles: return event->mId;
    case roles+1: return event->mName;
    case roles+2: return event->mDescription;
    case roles+3: return event->mFrom.toString();
    case roles+4: return event->mTo.toString();
    default: return QVariant();
    }
}

void SEventModel::fromJson(const QJsonArray &json)
{
    beginResetModel();
    SEventDB::fromJson(json);
    endResetModel();
}
