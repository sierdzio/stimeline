#ifndef SPERSONMODEL_H
#define SPERSONMODEL_H

#include "sperson.h"

#include <QAbstractListModel>
#include <QObject>

class SPersonModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit SPersonModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    QJsonArray toJson() const;
    void fromJson(const QJsonArray &json);

public slots:
    void addPerson(const QString &id,
                   const QString &picturePath,
                   const QString &name,
                   const QString &description);

protected:
    QVector<SPerson> mPeople;
};

#endif // SPERSONMODEL_H
