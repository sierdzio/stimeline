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
class SErasModel;
class SPlotsModel;

class SObjectModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit SObjectModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    bool removeRows(int row, int count, const QModelIndex &parent) override;

    void clear();
    QJsonArray toJson() const;
    void fromJson(const QJsonArray &json);

    void setErasModel(SErasModel *model);
    void setEra(const QByteArray &id, const QByteArray &from,
                const QByteArray &to);
    void setPlotsModel(SPlotsModel *model);

public slots:
    void addObject(const SObject &obj);
    void removeObject(const QByteArray &id);
    void removeSelectedObjects();
    void updateObject(const SObject &obj);
    void createEraFromSelection(const QString &name);
    void createPlotFromSelection(const QString &name, const QString &description = QString::null);

signals:
    void selectionModeChanged(const bool selectionMode) const;

protected:
    int findObjectIndex(const QByteArray &id) const;

    QVector<QByteArray> mSelected;
    SObjectContainer mObjects;
    SErasModel *mErasModel = nullptr;
    SPlotsModel *mPlotsModel = nullptr;
    const QHash<int, QByteArray> mRoleNames;
};
