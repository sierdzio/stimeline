#include "seventsortproxymodel.h"
#include "sdatetime.h"

//#include <QDebug>

SEventSortProxyModel::SEventSortProxyModel(QObject *parent)
    : QSortFilterProxyModel (parent)
{
}

bool SEventSortProxyModel::lessThan(const QModelIndex &left,
                                    const QModelIndex &right) const
{
    const QVariant leftData = sourceModel()->data(left, Qt::UserRole + 4);
    const QVariant rightData = sourceModel()->data(right, Qt::UserRole + 4);
    const SDateTime leftDT = SDateTime::fromString(leftData.toString());
    const SDateTime rightDT = SDateTime::fromString(rightData.toString());

    //qDebug() << "Less than. L:" << leftData.toString()
    //         << "R:" << rightData.toString();

    return leftDT < rightDT;
}
