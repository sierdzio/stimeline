#ifndef SEVENTSORTPROXYMODEL_H
#define SEVENTSORTPROXYMODEL_H

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

#endif // SEVENTSORTPROXYMODEL_H
