#include "sobjectsortproxymodel.h"
#include "sdatetime.h"

//#include <QDebug>

SObjectSortProxyModel::SObjectSortProxyModel(QObject *parent)
    : QSortFilterProxyModel (parent)
{
}

bool SObjectSortProxyModel::lessThan(const QModelIndex &left,
                                    const QModelIndex &right) const
{
    const QVariant leftData = sourceModel()->data(left, Qt::UserRole + 6);
    const QVariant rightData = sourceModel()->data(right, Qt::UserRole + 6);
    const SDateTime leftDT = SDateTime::fromString(leftData.toString());
    const SDateTime rightDT = SDateTime::fromString(rightData.toString());

    //qDebug() << "Less than. L:" << leftData.toString()
    //         << "R:" << rightData.toString();

    return leftDT < rightDT;
}
