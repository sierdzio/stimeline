#pragma once

#include <QObject>
#include <QSortFilterProxyModel>

class SObjectSortProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    SObjectSortProxyModel(QObject *parent = nullptr);

protected:
    virtual bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;
};
