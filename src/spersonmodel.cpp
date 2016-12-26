#include "spersonmodel.h"
#include "tags.h"

#include <QJsonArray>
#include <QJsonValue>

SPersonModel::SPersonModel(QObject *parent) : QAbstractListModel (parent)
{
}

QHash<int, QByteArray> SPersonModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    int i = Qt::UserRole + 1;
    roles[i++] = Tags::id;
    roles[i++] = Tags::picturePath;
    roles[i++] = Tags::name;
    roles[i++] = Tags::description;
    return roles;
}

int SPersonModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mPeople.count();
}

QVariant SPersonModel::data(const QModelIndex &index, int role) const
{
    const int row = index.row();
    const int roles = Qt::UserRole + 1;
    const SPerson person = mPeople.at(row);

    switch (role) {
    case roles: return person.mId;
    case roles+1: return person.mPicturePath;
    case roles+2: return person.mName;
    case roles+3: return person.mDescription;
    default: return QVariant();
    }
}

QJsonArray SPersonModel::toJson() const
{
    QJsonArray result;
    if (mPeople.isEmpty())
        return result;

    for (const SPerson &person: qAsConst(mPeople)) {
        result.append(person.toJson());
    }

    return result;
}

void SPersonModel::fromJson(const QJsonArray &json)
{
    beginResetModel();

    if (mPeople.isEmpty() == false)
        mPeople.clear();

    for (const QJsonValue &person: json) {
        mPeople.append(SPerson(person.toObject()));
    }

    endResetModel();
}

void SPersonModel::addPerson(const QString &id, const QString &picturePath,
                             const QString &name, const QString &description)
{
    beginInsertRows(QModelIndex(), mPeople.size(), mPeople.size());
    //auto event = SPerson(SPerson::InitialisationOption::DoNotInitialiseId);
    auto event = SPerson();
    event.mId = id.toLatin1();
    event.mPicturePath = picturePath.toLatin1();
    event.mName = name;
    event.mDescription = description;
    mPeople.append(event);
    endInsertRows();
}
