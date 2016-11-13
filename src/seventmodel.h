#ifndef SEVENTMODEL_H
#define SEVENTMODEL_H

#include "sevent.h"
#include "tags.h"

#include <QAbstractListModel>
#include <QByteArray>
#include <QHash>
#include <QVector>
#include <QVariant>
#include <QObject>

#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(seventmodel)

class QModelIndex;

class SEventModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit SEventModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    QJsonArray toJson() const;
    void fromJson(const QJsonArray &json);

public slots:
    QByteArray addEvent(const QString &name = QString::null,
                        const QString &description = QString::null,
                        const QString &from = QString::null,
                        const QString &to = QString::null);
    void updateEvent(const QString &id,
                     const QString &name,
                     const QString &description,
                     const QString &from,
                     const QString &to);
    QByteArray addEvent(const SEvent &event);
    void updateEvent(const SEvent &event);

protected:
    //QHash<QByteArray, SEvent> mEvents;
    QVector<SEvent> mEvents;
};

#endif // SEVENTMODEL_H
