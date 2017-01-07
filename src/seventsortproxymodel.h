#pragma once

#include <QObject>
#include <QSortFilterProxyModel>

class SEventSortProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    SEventSortProxyModel(QObject *parent = nullptr);

protected:
    virtual bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;
};
