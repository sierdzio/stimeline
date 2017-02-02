#include "sobjectsortproxymodel.h"
#include "sdatetime.h"

//#include <QDebug>

/*!
 * \class SObjectSortProxyModel
 *
 * Proxy model for SObjectModel, which enables the SObjects to be sorted according
 * to their "from" value (beginning date and time).
 */

/*!
 * Default constructor using \a parent.
 */
SObjectSortProxyModel::SObjectSortProxyModel(QObject *parent)
    : QSortFilterProxyModel (parent)
{
}

/*!
 * Sorting method. \a left and \a right represent 2 SObjects.
 */
bool SObjectSortProxyModel::lessThan(const QModelIndex &left,
                                     const QModelIndex &right) const
{
    const QVariant leftData = sourceModel()->data(left, Qt::UserRole + 6);
    const QVariant rightData = sourceModel()->data(right, Qt::UserRole + 6);
    const SDateTime leftDT(leftData.toString());
    const SDateTime rightDT(rightData.toString());

    //qDebug() << "Less than. L:" << leftData.toString()
    //         << "R:" << rightData.toString();

    return leftDT < rightDT;
}
