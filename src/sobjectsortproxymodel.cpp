#include "sobjectsortproxymodel.h"
#include "sdatetime.h"
#include "sobject.h"
#include "tags.h"

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
    const int role = Tags::sobjectRole;
    const SObject leftObject = sourceModel()->data(left, role).value<SObject>();
    const SObject rightObject = sourceModel()->data(right, role).value<SObject>();
    const SDateTime leftDT(leftObject.mFrom);
    const SDateTime rightDT(rightObject.mFrom);
    const bool result = leftDT < rightDT;

    //qDebug() << "Less than. L:" << leftDT.toString()
    //         << "R:" << rightDT.toString()
    //         << "is:" << result;

    return result;
}
